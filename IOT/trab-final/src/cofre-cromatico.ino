#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_TCS34725.h>
#include <TFT_eSPI.h>

// TTGO T-Display: botoes onboard. GPIO35 nao possui pull-up interno.
constexpr uint8_t BTN_A_PIN = 0;
constexpr uint8_t BTN_B_PIN = 35;

// I2C escolhido para o TCS34725. Confirme se GPIO21/22 estao livres
constexpr uint8_t I2C_SDA_PIN = 21;
constexpr uint8_t I2C_SCL_PIN = 22;

const char MOCK_PASSWORD[] = "58321";

constexpr uint8_t CARD_COUNT = 4;
constexpr uint8_t PERMUTATION_COUNT = 24;
constexpr uint8_t SAMPLES_PER_READING = 8;
constexpr uint16_t MIN_CLEAR_VALUE = 15;
constexpr float MAX_COLOR_DISTANCE = 0.22f;
constexpr float MIN_CARD_SEPARATION = 0.07f;
constexpr uint32_t DEBOUNCE_MS = 220;

// ------------------------- Objetos -------------------------
TFT_eSPI tft = TFT_eSPI();
Adafruit_TCS34725 colorSensor(
  TCS34725_INTEGRATIONTIME_50MS,
  TCS34725_GAIN_4X
);

struct ColorSample {
  float r;
  float g;
  float b;
  uint16_t clear;
};

ColorSample referenceCards[CARD_COUNT];
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

void showMessage(const String &line1, const String &line2 = "", const String &line3 = "") {
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextDatum(TL_DATUM);
  tft.setTextSize(2);
  tft.drawString("COFRE CROMATICO", 8, 8);
  tft.drawFastHLine(8, 34, 220, TFT_DARKGREY);
  tft.setTextSize(1);
  tft.drawString(line1, 8, 48);
  if (line2.length()) tft.drawString(line2, 8, 68);
  if (line3.length()) tft.drawString(line3, 8, 88);
}

// Calcula senha % 24 sem converter a senha inteira para um tipo limitado.
int passwordToPermutationIndex(const char *password) {
  int remainder = 0;
  for (size_t i = 0; password[i] != '\0'; i++) {
    if (password[i] < '0' || password[i] > '9') return -1;
    remainder = (remainder * 10 + (password[i] - '0')) % PERMUTATION_COUNT;
  }
  return remainder;
}

// Gera a permutacao lexicografica de indice 0..23 para os IDs 1,2,3,4.
void indexToPermutation(uint8_t index, uint8_t output[CARD_COUNT]) {
  uint8_t available[CARD_COUNT] = {1, 2, 3, 4};
  uint8_t count = CARD_COUNT;
  const uint8_t factorials[CARD_COUNT] = {6, 2, 1, 1};

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

bool readColor(ColorSample &result) {
  if (!sensorReady) return false;

  uint32_t sumR = 0, sumG = 0, sumB = 0, sumC = 0;
  for (uint8_t i = 0; i < SAMPLES_PER_READING; i++) {
    uint16_t r, g, b, c;
    colorSensor.getRawData(&r, &g, &b, &c);
    sumR += r;
    sumG += g;
    sumB += b;
    sumC += c;
    delay(60);
  }

  float r = (float)sumR / SAMPLES_PER_READING;
  float g = (float)sumG / SAMPLES_PER_READING;
  float b = (float)sumB / SAMPLES_PER_READING;
  result.clear = (uint16_t)(sumC / SAMPLES_PER_READING);

  float total = r + g + b;
  if (result.clear < MIN_CLEAR_VALUE || total <= 0.0f) return false;

  result.r = r / total;
  result.g = g / total;
  result.b = b / total;
  return true;
}

float colorDistance(const ColorSample &a, const ColorSample &b) {
  float dr = a.r - b.r;
  float dg = a.g - b.g;
  float db = a.b - b.b;
  return sqrtf(dr * dr + dg * dg + db * db);
}

// Retorna o ID do cartao mais proximo (1..4), ou 0 se nao houver confianca.
uint8_t identifyCard(const ColorSample &sample) {
  float bestDistance = 999.0f;
  uint8_t bestId = 0;

  for (uint8_t i = 0; i < registeredCount; i++) {
    float distance = colorDistance(sample, referenceCards[i]);
    if (distance < bestDistance) {
      bestDistance = distance;
      bestId = i + 1;
    }
  }

  return (bestDistance <= MAX_COLOR_DISTANCE) ? bestId : 0;
}

bool buttonPressed(uint8_t pin, bool &lastState, uint32_t &lastChange) {
  bool current = digitalRead(pin);
  uint32_t now = millis();
  if (current != lastState) {
    lastState = current;
    lastChange = now;
  }
  return (current == LOW && (now - lastChange) > DEBOUNCE_MS);
}

bool sequenceContains(uint8_t id) {
  for (uint8_t i = 0; i < enteredCount; i++) {
    if (enteredSequence[i] == id) return true;
  }
  return false;
}

void printTargetToSerial() {
  Serial.print("Senha mock: ");
  Serial.println(MOCK_PASSWORD);
  Serial.print("Indice (senha % 24): ");
  Serial.println(passwordToPermutationIndex(MOCK_PASSWORD));
  Serial.print("Sequencia esperada (IDs): ");
  for (uint8_t i = 0; i < CARD_COUNT; i++) {
    Serial.print(targetSequence[i]);
    if (i < CARD_COUNT - 1) Serial.print(" -> ");
  }
  Serial.println();
}

void showRegisterScreen() {
  showMessage("CADASTRE OS 4 CARTOES", "Aproxime o cartao e", "pressione A para salvar");
  tft.drawString("Lidos: " + String(registeredCount) + "/4", 8, 112);
}

void showEnterScreen() {
  showMessage("INSIRA A SEQUENCIA", "Apresente os cartoes na", "ordem que voce descobriu");
  String current = "Entrada: ";
  for (uint8_t i = 0; i < enteredCount; i++) {
    current += String(enteredSequence[i]);
    if (i < enteredCount - 1) current += " > ";
  }
  tft.drawString(current, 8, 112);
  tft.drawString("A: ler | B: confirmar", 8, 132);
}

void resetEnteredSequence() {
  enteredCount = 0;
  memset(enteredSequence, 0, sizeof(enteredSequence));
}

void registerCurrentCard() {
  if (registeredCount >= CARD_COUNT) return;

  showMessage("LENDO CARTAO", "Mantenha parado...");
  ColorSample sample;
  if (!readColor(sample)) {
    showMessage("LEITURA INVALIDA", "Verifique luz/distancia", "Tente novamente com A");
    Serial.println("Falha: leitura sem luz suficiente ou invalida.");
    delay(900);
    showRegisterScreen();
    return;
  }

  for (uint8_t i = 0; i < registeredCount; i++) {
    if (colorDistance(sample, referenceCards[i]) < MIN_CARD_SEPARATION) {
      showMessage("CARTAO MUITO PARECIDO", "Use uma amostra diferente", "e tente novamente");
      Serial.println("Falha: cartao muito parecido com um ja cadastrado.");
      delay(1200);
      showRegisterScreen();
      return;
    }
  }

  referenceCards[registeredCount] = sample;
  registeredCount++;
  Serial.printf("Cartao %u cadastrado: R=%.3f G=%.3f B=%.3f Clear=%u\n",
                registeredCount, sample.r, sample.g, sample.b, sample.clear);

  if (registeredCount == CARD_COUNT) {
    state = STATE_ENTERING;
    resetEnteredSequence();
    showMessage("CARTOES CADASTRADOS", "Agora descubra a ordem", "A: ler cartao");
    delay(1200);
    showEnterScreen();
  } else {
    showRegisterScreen();
  }
}

void captureSequenceCard() {
  if (enteredCount >= CARD_COUNT) return;

  showMessage("IDENTIFICANDO...", "Mantenha o cartao", "parado sobre o sensor");
  ColorSample sample;
  if (!readColor(sample)) {
    showMessage("LEITURA INVALIDA", "Aproxime melhor o cartao", "e tente novamente");
    delay(900);
    showEnterScreen();
    return;
  }

  uint8_t id = identifyCard(sample);
  if (id == 0) {
    showMessage("COR NAO RECONHECIDA", "Confira iluminacao", "e tente novamente");
    Serial.println("Cartao nao reconhecido: distancia acima do limite.");
    delay(1100);
    showEnterScreen();
    return;
  }

  if (sequenceContains(id)) {
    showMessage("CARTAO REPETIDO", "Cada cartao deve aparecer", "uma unica vez");
    delay(1000);
    showEnterScreen();
    return;
  }

  enteredSequence[enteredCount++] = id;
  Serial.printf("Posicao %u: cartao %u\n", enteredCount, id);
  showEnterScreen();
}

void validateSequence() {
  if (enteredCount != CARD_COUNT) {
    showMessage("SEQUENCIA INCOMPLETA", "Leia os 4 cartoes", "antes de confirmar");
    delay(1000);
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
    showMessage("COFRE DESBLOQUEADO!", "Sequencia correta", "Parabens!");
    Serial.println("RESULTADO: SUCESSO");
  } else {
    state = STATE_ERROR;
    showMessage("COMBINACAO INCORRETA", "Tente novamente", "Pressione A para resetar");
    Serial.println("RESULTADO: FALHA");
    resetEnteredSequence();
  }
}

void setup() {
  Serial.begin(115200);
  delay(200);

  pinMode(BTN_A_PIN, INPUT_PULLUP);
  pinMode(BTN_B_PIN, INPUT);

  tft.init();
  tft.setRotation(1);
  showMessage("INICIALIZANDO...", "Sensor TCS34725", "Aguarde");

  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
  sensorReady = colorSensor.begin();

  if (!sensorReady) {
    showMessage("ERRO NO SENSOR", "Verifique SDA/SCL", "e alimentacao");
    Serial.println("ERRO: TCS34725 nao encontrado no I2C.");
    while (true) delay(1000);
  }

  int permutationIndex = passwordToPermutationIndex(MOCK_PASSWORD);
  if (permutationIndex < 0) {
    showMessage("ERRO NA SENHA MOCK", "Use apenas numeros");
    while (true) delay(1000);
  }
  indexToPermutation((uint8_t)permutationIndex, targetSequence);
  printTargetToSerial();

  Serial.println("Sensor TCS34725 pronto.");
  showRegisterScreen();
}

void loop() {
  bool pressA = buttonPressed(BTN_A_PIN, lastA, lastAChange);
  bool pressB = buttonPressed(BTN_B_PIN, lastB, lastBChange);

  static bool handledA = false;
  static bool handledB = false;
  bool rawA = digitalRead(BTN_A_PIN);
  bool rawB = digitalRead(BTN_B_PIN);

  if (rawA == HIGH) handledA = false;
  if (rawB == HIGH) handledB = false;

  if (pressA && !handledA) {
    handledA = true;
    if (state == STATE_REGISTERING) {
      registerCurrentCard();
    } else if (state == STATE_ENTERING) {
      captureSequenceCard();
    } else if (state == STATE_ERROR) {
      state = STATE_ENTERING;
      resetEnteredSequence();
      showEnterScreen();
    }
  }

  if (pressB && !handledB) {
    handledB = true;
    if (state == STATE_ENTERING) {
      validateSequence();
    }
  }

  delay(10);
}
