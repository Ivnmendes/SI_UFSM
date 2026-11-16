
#include <Arduino.h>
#include <Wire.h>
#include <math.h>
#include <string.h>
#include <SparkFun_APDS9960.h>
#include <TFT_eSPI.h>

// =====================================================
// CONFIGURACOES DE HARDWARE
// =====================================================

// TTGO T-Display original:
// Botao A: GPIO 0
// Botao B: GPIO 35
//
// GPIO 35 nao possui pull-up interno.
// Na placa original, utilize o circuito do botao onboard.

constexpr uint8_t BTN_A_PIN = 0;
constexpr uint8_t BTN_B_PIN = 35;

constexpr uint8_t I2C_SDA_PIN = 21;
constexpr uint8_t I2C_SCL_PIN = 22;

// =====================================================
// CONFIGURACOES DO JOGO
// =====================================================

// Senha temporaria usada para gerar a sequencia.
// Posteriormente sera substituida pela regra recebida via MQTT.
const char MOCK_PASSWORD[] = "58321";

constexpr uint8_t CARD_COUNT = 4;
constexpr uint8_t PERMUTATION_COUNT = 24;

constexpr uint8_t SAMPLES_PER_READING = 8;

// Distancia maxima entre a leitura atual e a referencia.
// Valor inicial: precisa ser validado com os cartoes reais.
constexpr float MAX_COLOR_DISTANCE = 0.15f;

// Distancia minima entre duas referencias cadastradas.
// Evita cadastrar duas amostras praticamente iguais.
constexpr float MIN_CARD_SEPARATION = 0.07f;

constexpr uint32_t DEBOUNCE_MS = 220;

// Tempo aproximado entre leituras do sensor.
// O APDS-9960 precisa de tempo para integrar a luz.
constexpr uint16_t SENSOR_SAMPLE_DELAY_MS = 110;

// =====================================================
// OBJETOS
// =====================================================

TFT_eSPI tft = TFT_eSPI();
SparkFun_APDS9960 colorSensor;

// =====================================================
// ESTRUTURAS E VARIAVEIS
// =====================================================

struct ColorSample {
  float r;
  float g;
  float b;
  uint16_t clear;
};

// Referencias RGB cadastradas durante a primeira fase.
ColorSample referenceCards[CARD_COUNT];

// Sequencia correta e sequencia inserida.
uint8_t targetSequence[CARD_COUNT];
uint8_t enteredSequence[CARD_COUNT];

uint8_t enteredCount = 0;
uint8_t registeredCount = 0;
uint8_t attempts = 0;

bool sensorReady = false;

bool lastA = HIGH;
bool lastB = HIGH;

uint32_t lastAChange = 0;
uint32_t lastBChange = 0;

enum GameState {
  STATE_REGISTERING,
  STATE_ENTERING,
  STATE_SUCCESS,
  STATE_ERROR
};

GameState state = STATE_REGISTERING;

// =====================================================
// DISPLAY
// =====================================================

void showMessage(
  const String &line1,
  const String &line2 = "",
  const String &line3 = ""
) {
  tft.fillScreen(TFT_BLACK);

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextDatum(TL_DATUM);

  tft.setTextSize(2);
  tft.drawString("COFRE CROMATICO", 8, 8);

  tft.drawFastHLine(8, 34, 220, TFT_DARKGREY);

  tft.setTextSize(1);

  if (line1.length()) {
    tft.drawString(line1, 8, 48);
  }

  if (line2.length()) {
    tft.drawString(line2, 8, 68);
  }

  if (line3.length()) {
    tft.drawString(line3, 8, 88);
  }
}

// =====================================================
// CONVERSAO DA SENHA EM PERMUTACAO
// =====================================================

// Calcula senha % 24 sem converter a senha inteira
// para um tipo numerico limitado.
int passwordToPermutationIndex(const char *password) {
  int remainder = 0;

  for (size_t i = 0; password[i] != '\0'; i++) {
    if (password[i] < '0' || password[i] > '9') {
      return -1;
    }

    remainder = (
      remainder * 10 + (password[i] - '0')
    ) % PERMUTATION_COUNT;
  }

  return remainder;
}

// Gera a permutacao lexicografica de indice 0 a 23.
// Os IDs dos cartoes sao 1, 2, 3 e 4.
void indexToPermutation(
  uint8_t index,
  uint8_t output[CARD_COUNT]
) {
  uint8_t available[CARD_COUNT] = {1, 2, 3, 4};

  uint8_t count = CARD_COUNT;

  const uint8_t factorials[CARD_COUNT] = {
    6, 2, 1, 1
  };

  for (uint8_t position = 0; position < CARD_COUNT; position++) {
    uint8_t factor = factorials[position];

    uint8_t selected = index / factor;

    index %= factor;

    output[position] = available[selected];

    for (uint8_t j = selected; j + 1 < count; j++) {
      available[j] = available[j + 1];
    }

    count--;
  }
}

// =====================================================
// LEITURA DO SENSOR APDS-9960
// =====================================================

bool readColor(ColorSample &result) {
  if (!sensorReady) {
    return false;
  }

  uint32_t sumR = 0;
  uint32_t sumG = 0;
  uint32_t sumB = 0;
  uint32_t sumC = 0;

  for (uint8_t i = 0; i < SAMPLES_PER_READING; i++) {
    uint16_t r, g, b, c;

    bool okR = colorSensor.readRedLight(r);
    bool okG = colorSensor.readGreenLight(g);
    bool okB = colorSensor.readBlueLight(b);
    bool okC = colorSensor.readAmbientLight(c);

    if (!okR || !okG || !okB || !okC) {
      Serial.println("Erro ao ler os canais do APDS-9960.");
      return false;
    }

    sumR += r;
    sumG += g;
    sumB += b;
    sumC += c;

    delay(SENSOR_SAMPLE_DELAY_MS);
  }

  // Calcula a media das amostras.
  result.r = (float)sumR / SAMPLES_PER_READING;
  result.g = (float)sumG / SAMPLES_PER_READING;
  result.b = (float)sumB / SAMPLES_PER_READING;
  result.clear = (uint16_t)(sumC / SAMPLES_PER_READING);

  // Exibe os valores calculados no monitor serial.
  Serial.printf(
    "R: %.2f | G: %.2f | B: %.2f | Clear: %u\n",
    result.r,
    result.g,
    result.b,
    result.clear
  );

  // Evita aceitar uma leitura sem sinal RGB.
  if ((result.r + result.g + result.b) <= 0) {
    Serial.println("Leitura sem sinal RGB valido.");
    return false;
  }

  return true;
}

// =====================================================
// COMPARACAO DE CORES
// =====================================================

// Calcula a distancia entre duas cores utilizando
// os canais RGB normalizados.
//
// A normalizacao reduz a influencia da intensidade
// geral da iluminacao sobre a comparacao.
float colorDistance(
  const ColorSample &a,
  const ColorSample &b
) {
  float totalA = a.r + a.g + a.b;
  float totalB = b.r + b.g + b.b;

  if (totalA <= 0 || totalB <= 0) {
    return 999.0f;
  }

  float ar = a.r / totalA;
  float ag = a.g / totalA;
  float ab = a.b / totalA;

  float br = b.r / totalB;
  float bg = b.g / totalB;
  float bb = b.b / totalB;

  float dr = ar - br;
  float dg = ag - bg;
  float db = ab - bb;

  return sqrtf(
    dr * dr +
    dg * dg +
    db * db
  );
}

// Retorna o ID do cartao mais proximo.
//
// IDs:
// 1 = Vermelho
// 2 = Amarelo
// 3 = Verde
// 4 = Azul
//
// Retorna 0 quando a leitura nao e suficientemente
// proxima de nenhuma referencia.
uint8_t identifyCard(const ColorSample &sample) {
  float bestDistance = 999.0f;

  uint8_t bestId = 0;

  for (uint8_t i = 0; i < registeredCount; i++) {
    float distance = colorDistance(
      sample,
      referenceCards[i]
    );

    if (distance < bestDistance) {
      bestDistance = distance;
      bestId = i + 1;
    }
  }

  Serial.printf(
    "Cartao mais proximo: %u | Distancia: %.4f\n",
    bestId,
    bestDistance
  );

  if (bestDistance <= MAX_COLOR_DISTANCE) {
    return bestId;
  }

  return 0;
}

// =====================================================
// BOTOES
// =====================================================

bool buttonPressed(
  uint8_t pin,
  bool &lastState,
  uint32_t &lastChange
) {
  bool current = digitalRead(pin);

  uint32_t now = millis();

  if (current != lastState) {
    lastState = current;
    lastChange = now;
  }

  return (
    current == LOW &&
    (now - lastChange) > DEBOUNCE_MS
  );
}

// =====================================================
// CONTROLE DA SEQUENCIA
// =====================================================

bool sequenceContains(uint8_t id) {
  for (uint8_t i = 0; i < enteredCount; i++) {
    if (enteredSequence[i] == id) {
      return true;
    }
  }

  return false;
}

void resetEnteredSequence() {
  enteredCount = 0;

  memset(
    enteredSequence,
    0,
    sizeof(enteredSequence)
  );
}

// =====================================================
// DEBUG
// =====================================================

void printTargetToSerial() {
  Serial.println();
  Serial.println("========== COFRE CROMATICO ==========");

  Serial.print("Senha mock: ");
  Serial.println(MOCK_PASSWORD);

  Serial.print("Indice (senha % 24): ");
  Serial.println(
    passwordToPermutationIndex(MOCK_PASSWORD)
  );

  Serial.print("Sequencia esperada (IDs): ");

  for (uint8_t i = 0; i < CARD_COUNT; i++) {
    Serial.print(targetSequence[i]);

    if (i < CARD_COUNT - 1) {
      Serial.print(" -> ");
    }
  }

  Serial.println();
  Serial.println("=====================================");
  Serial.println();
}

// =====================================================
// TELAS DO JOGO
// =====================================================

void showRegisterScreen() {
  showMessage(
    "CADASTRE OS CARTOES",
    "1 Vermelho  2 Amarelo",
    "3 Verde     4 Azul"
  );

  tft.drawString(
    "A: salvar cartao",
    8,
    108
  );

  tft.drawString(
    "Lidos: " + String(registeredCount) + "/4",
    8,
    124
  );
}

void showEnterScreen() {
  showMessage(
    "INSIRA A SEQUENCIA",
    "Apresente os cartoes na",
    "ordem que voce descobriu"
  );

  String current = "Entrada: ";

  for (uint8_t i = 0; i < enteredCount; i++) {
    current += String(enteredSequence[i]);

    if (i < enteredCount - 1) {
      current += " > ";
    }
  }

  tft.drawString(current, 8, 108);

  tft.drawString(
    "A: ler cartao",
    8,
    122
  );

  tft.drawString(
    "B: confirmar",
    130,
    122
  );
}

// =====================================================
// CADASTRO DOS CARTOES
// =====================================================

void registerCurrentCard() {
  if (registeredCount >= CARD_COUNT) {
    return;
  }

  showMessage(
    "LENDO CARTAO",
    "Mantenha parado...",
    "Aguarde"
  );

  ColorSample sample;

  if (!readColor(sample)) {
    showMessage(
      "LEITURA INVALIDA",
      "Verifique luz/distancia",
      "Tente novamente com A"
    );

    Serial.println(
      "Falha na leitura durante cadastro."
    );

    delay(1200);

    showRegisterScreen();

    return;
  }

  // Verifica se a nova amostra e muito parecida
  // com algum cartao ja cadastrado.
  for (uint8_t i = 0; i < registeredCount; i++) {
    float distance = colorDistance(
      sample,
      referenceCards[i]
    );

    if (distance < MIN_CARD_SEPARATION) {
      showMessage(
        "CARTAO MUITO PARECIDO",
        "Use outra amostra",
        "e tente novamente"
      );

      Serial.printf(
        "Cartao rejeitado. Distancia da referencia %u: %.4f\n",
        i + 1,
        distance
      );

      delay(1400);

      showRegisterScreen();

      return;
    }
  }

  // Salva a referencia na ordem do cadastro.
  referenceCards[registeredCount] = sample;

  registeredCount++;

  Serial.printf(
    "Cartao %u cadastrado: R=%.2f G=%.2f B=%.2f Clear=%u\n",
    registeredCount,
    sample.r,
    sample.g,
    sample.b,
    sample.clear
  );

  if (registeredCount == CARD_COUNT) {
    state = STATE_ENTERING;

    resetEnteredSequence();

    showMessage(
      "CARTOES CADASTRADOS",
      "Agora descubra a ordem",
      "A: ler cartao"
    );

    delay(1400);

    showEnterScreen();
  } else {
    showRegisterScreen();
  }
}

// =====================================================
// LEITURA DA SEQUENCIA
// =====================================================

void captureSequenceCard() {
  if (enteredCount >= CARD_COUNT) {
    return;
  }

  showMessage(
    "IDENTIFICANDO...",
    "Mantenha o cartao",
    "parado sobre o sensor"
  );

  ColorSample sample;

  if (!readColor(sample)) {
    showMessage(
      "LEITURA INVALIDA",
      "Aproxime melhor o cartao",
      "e tente novamente"
    );

    delay(1200);

    showEnterScreen();

    return;
  }

  uint8_t id = identifyCard(sample);

  if (id == 0) {
    showMessage(
      "COR NAO RECONHECIDA",
      "Confira iluminacao",
      "e tente novamente"
    );

    Serial.println(
      "Cartao nao reconhecido."
    );

    delay(1300);

    showEnterScreen();

    return;
  }

  if (sequenceContains(id)) {
    showMessage(
      "CARTAO REPETIDO",
      "Cada cartao deve aparecer",
      "uma unica vez"
    );

    delay(1200);

    showEnterScreen();

    return;
  }

  enteredSequence[enteredCount] = id;

  enteredCount++;

  Serial.printf(
    "Posicao %u: cartao %u\n",
    enteredCount,
    id
  );

  showEnterScreen();
}

// =====================================================
// VALIDACAO
// =====================================================

void validateSequence() {
  if (enteredCount != CARD_COUNT) {
    showMessage(
      "SEQUENCIA INCOMPLETA",
      "Leia os 4 cartoes",
      "antes de confirmar"
    );

    delay(1200);

    showEnterScreen();

    return;
  }

  attempts++;

  bool correct = true;

  for (uint8_t i = 0; i < CARD_COUNT; i++) {
    if (enteredSequence[i] != targetSequence[i]) {
      correct = false;
      break;
    }
  }

  if (correct) {
    state = STATE_SUCCESS;

    showMessage(
      "COFRE DESBLOQUEADO!",
      "Sequencia correta",
      "Parabens!"
    );

    Serial.println();
    Serial.println("RESULTADO: SUCESSO");

    Serial.printf(
      "Tentativas: %u\n",
      attempts
    );
  } else {
    state = STATE_ERROR;

    showMessage(
      "COMBINACAO INCORRETA",
      "Tente novamente",
      "A: reiniciar sequencia"
    );

    Serial.println();
    Serial.println("RESULTADO: FALHA");

    Serial.printf(
      "Tentativa: %u\n",
      attempts
    );

    resetEnteredSequence();
  }
}

// =====================================================
// INICIALIZACAO
// =====================================================

void setup() {
  Serial.begin(115200);

  delay(200);

  // Configuracao dos botoes.
  pinMode(BTN_A_PIN, INPUT_PULLUP);

  // GPIO35 e somente entrada e nao possui pull-up interno.
  // O circuito da placa deve fornecer o nivel HIGH em repouso.
  pinMode(BTN_B_PIN, INPUT);

  // Inicializa o display.
  tft.init();

  tft.setRotation(1);

  showMessage(
    "INICIALIZANDO...",
    "Sensor APDS-9960",
    "Aguarde"
  );

  // Inicializa I2C.
  Wire.begin(
    I2C_SDA_PIN,
    I2C_SCL_PIN
  );

  Wire.setClock(100000);

  // Inicializa o APDS-9960.
  sensorReady = colorSensor.init();

  if (sensorReady) {
    sensorReady = colorSensor.enableLightSensor(false);
  }

  // Interrompe a inicializacao se o sensor falhar.
  if (!sensorReady) {
    Serial.println(
      "ERRO: APDS-9960 nao inicializado!"
    );

    showMessage(
      "ERRO NO SENSOR",
      "Verifique o APDS-9960",
      "Reinicie o dispositivo"
    );

    while (true) {
      delay(1000);
    }
  }

  Serial.println(
    "APDS-9960 inicializado corretamente!"
  );

  // Aguarda o sensor estabilizar.
  delay(200);

  // Gera a sequencia esperada.
  int permutationIndex = passwordToPermutationIndex(
    MOCK_PASSWORD
  );

  if (permutationIndex < 0) {
    showMessage(
      "ERRO NA SENHA MOCK",
      "Use apenas numeros"
    );

    Serial.println(
      "Erro: senha mock invalida."
    );

    while (true) {
      delay(1000);
    }
  }

  indexToPermutation(
    (uint8_t)permutationIndex,
    targetSequence
  );

  printTargetToSerial();

  Serial.println(
    "Sistema pronto para cadastro."
  );

  showRegisterScreen();
}

// =====================================================
// LOOP PRINCIPAL
// =====================================================

void loop() {
  bool pressA = buttonPressed(
    BTN_A_PIN,
    lastA,
    lastAChange
  );

  bool pressB = buttonPressed(
    BTN_B_PIN,
    lastB,
    lastBChange
  );

  // Impede repeticao enquanto o botao permanecer pressionado.
  static bool handledA = false;
  static bool handledB = false;

  bool rawA = digitalRead(BTN_A_PIN);
  bool rawB = digitalRead(BTN_B_PIN);

  if (rawA == HIGH) {
    handledA = false;
  }

  if (rawB == HIGH) {
    handledB = false;
  }

  // -------------------------
  // BOTAO A
  // -------------------------

  if (pressA && !handledA) {
    handledA = true;

    if (state == STATE_REGISTERING) {
      registerCurrentCard();
    }

    else if (state == STATE_ENTERING) {
      captureSequenceCard();
    }

    else if (state == STATE_ERROR) {
      state = STATE_ENTERING;

      resetEnteredSequence();

      showEnterScreen();
    }
  }

  // -------------------------
  // BOTAO B
  // -------------------------

  if (pressB && !handledB) {
    handledB = true;

    if (state == STATE_ENTERING) {
      validateSequence();
    }
  }

  delay(10);
}
