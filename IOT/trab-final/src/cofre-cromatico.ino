#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <math.h>
#include <string.h>
#include <SparkFun_APDS9960.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

// =====================================================
// PINOS DA TTGO T-DISPLAY ORIGINAL (ESP32)
// =====================================================

constexpr uint8_t BTN_A_PIN = 0;   // Botao esquerdo (possui pull-up interno)
constexpr uint8_t BTN_B_PIN = 35;  // Botao direito (pull-up fisico na placa)

// Pinos internos do display ST7789 (135x240)
constexpr int8_t TFT_MOSI_PIN = 19;
constexpr int8_t TFT_SCLK_PIN = 18;
constexpr int8_t TFT_CS_PIN   = 5;
constexpr int8_t TFT_DC_PIN   = 16;
constexpr int8_t TFT_RST_PIN  = 23;
constexpr int8_t TFT_BL_PIN   = 4;

// Barramento I2C do sensor APDS-9960
constexpr uint8_t I2C_SDA_PIN = 21;
constexpr uint8_t I2C_SCL_PIN = 22;

// =====================================================
// CORES RGB565 PARA O DISPLAY
// =====================================================

constexpr uint16_t C_BLACK    = 0x0000;
constexpr uint16_t C_WHITE    = 0xFFFF;
constexpr uint16_t C_DARKGREY = 0x4208;
constexpr uint16_t C_CYAN     = 0x07FF;
constexpr uint16_t C_RED      = 0xF800;
constexpr uint16_t C_YELLOW   = 0xFFE0;
constexpr uint16_t C_GREEN    = 0x07E0;
constexpr uint16_t C_BLUE     = 0x03FF;
constexpr uint16_t C_ORANGE   = 0xFD20;

// =====================================================
// CONFIGURACOES DO JOGO, CALIBRACAO E REGRAS
// =====================================================

constexpr uint8_t CARD_COUNT = 4;
constexpr uint8_t PERMUTATION_COUNT = 24;
constexpr uint8_t SAMPLES_PER_READING = 8;

constexpr float MAX_COLOR_DISTANCE = 0.16f;
constexpr float MIN_CARD_SEPARATION = 0.06f;

constexpr uint32_t DEBOUNCE_MS = 50;
constexpr uint16_t SENSOR_SAMPLE_DELAY_MS = 80;

// Lista de regras mockadas para testar sem MQTT (futuramente vira do topico MQTT)
constexpr uint8_t MOCK_RULES_COUNT = 5;
const char *MOCK_RULES[MOCK_RULES_COUNT] = {
  "BLUE_ASCENDING",
  "GREEN_DESCENDING",
  "RED_ASCENDING",
  "CLEAR_ASCENDING",
  "58321" // Fallback numerico (senha % 24)
};

uint8_t currentRuleIndex = 0;
String activeRuleCode = MOCK_RULES[0];
String currentRuleHint = "";

const char *CARD_NAMES[CARD_COUNT] = {
  "Vermelho",
  "Amarelo",
  "Verde",
  "Azul"
};

const char *CARD_SHORT[CARD_COUNT] = {
  "VM",
  "AM",
  "VD",
  "AZ"
};

const uint16_t CARD_UI_COLORS[CARD_COUNT] = {
  C_RED,
  C_YELLOW,
  C_GREEN,
  C_BLUE
};

// =====================================================
// OBJETOS GLOBAIS
// =====================================================

SPIClass tftSPI(VSPI);
Adafruit_ST7789 tft = Adafruit_ST7789(&tftSPI, TFT_CS_PIN, TFT_DC_PIN, TFT_RST_PIN);
SparkFun_APDS9960 colorSensor;

// =====================================================
// ESTRUTURAS E VARIAVEIS DE ESTADO
// =====================================================

struct ColorSample {
  float r;
  float g;
  float b;
  uint16_t clear;
};

struct ButtonTracker {
  uint8_t pin;
  bool stableState;
  bool lastReading;
  uint32_t lastDebounceTime;
};

ButtonTracker btnA = {BTN_A_PIN, HIGH, HIGH, 0};
ButtonTracker btnB = {BTN_B_PIN, HIGH, HIGH, 0};

ColorSample referenceCards[CARD_COUNT];

uint8_t targetSequence[CARD_COUNT];
uint8_t enteredSequence[CARD_COUNT];

uint8_t enteredCount = 0;
uint8_t registeredCount = 0;
uint8_t attempts = 0;

bool sensorReady = false;

enum GameState {
  STATE_REGISTERING,
  STATE_ENTERING,
  STATE_SUCCESS,
  STATE_ERROR
};

GameState state = STATE_REGISTERING;

enum RuleChannel {
  CH_RED_NORM,
  CH_GREEN_NORM,
  CH_BLUE_NORM,
  CH_CLEAR_RAW
};

// =====================================================
// LEITURA DE BOTOES COM DEBOUNCE
// =====================================================

bool checkButtonClick(ButtonTracker &btn, const char *debugName) {
  bool reading = digitalRead(btn.pin);
  uint32_t now = millis();

  if (reading != btn.lastReading) {
    btn.lastDebounceTime = now;
    btn.lastReading = reading;
  }

  if ((now - btn.lastDebounceTime) > DEBOUNCE_MS) {
    if (reading != btn.stableState) {
      btn.stableState = reading;
      if (btn.stableState == LOW) {
        Serial.printf("[ENTRADA] %s pressionado (GPIO %u)\n", debugName, btn.pin);
        return true;
      }
    }
  }

  return false;
}

// =====================================================
// MOTOR DE REGRAS (CANAIS RGB/CLEAR + PERMUTACAO)
// =====================================================

// Extrai o valor de comparacao de um cartao calibrado conforme o canal da regra
float getCardMetric(const ColorSample &card, RuleChannel channel) {
  float total = card.r + card.g + card.b;
  if (total <= 0.0f) total = 1.0f;

  switch (channel) {
    case CH_RED_NORM:   return card.r / total;
    case CH_GREEN_NORM: return card.g / total;
    case CH_BLUE_NORM:  return card.b / total;
    case CH_CLEAR_RAW:  return (float)card.clear;
  }
  return 0.0f;
}

// Ordena os IDs {1, 2, 3, 4} pelo canal escolhido (crescente ou decrescente)
void buildSequenceByChannel(RuleChannel channel, bool ascending, uint8_t output[CARD_COUNT]) {
  uint8_t ids[CARD_COUNT] = {1, 2, 3, 4};
  float metrics[CARD_COUNT];

  for (uint8_t i = 0; i < CARD_COUNT; i++) {
    metrics[i] = getCardMetric(referenceCards[i], channel);
  }

  // Insertion sort estavel (em caso de empate tecnico, mantem a ordem do ID)
  for (uint8_t i = 1; i < CARD_COUNT; i++) {
    uint8_t keyId = ids[i];
    float keyVal  = metrics[i];
    int8_t j = i - 1;

    while (j >= 0 && (ascending ? (metrics[j] > keyVal) : (metrics[j] < keyVal))) {
      ids[j + 1]     = ids[j];
      metrics[j + 1] = metrics[j];
      j--;
    }
    ids[j + 1]     = keyId;
    metrics[j + 1] = keyVal;
  }

  for (uint8_t i = 0; i < CARD_COUNT; i++) {
    output[i] = ids[i];
  }
}

int passwordToPermutationIndex(const char *password) {
  int remainder = 0;
  for (size_t i = 0; password[i] != '\0'; i++) {
    if (password[i] < '0' || password[i] > '9') return -1;
    remainder = (remainder * 10 + (password[i] - '0')) % PERMUTATION_COUNT;
  }
  return remainder;
}

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

// Interpreta a string da regra (vinda do array mock ou futuramente do JSON MQTT)
void applyActiveRule(const String &ruleStr) {
  String r = ruleStr;
  r.trim();
  r.toUpperCase();

  if (r == "BLUE_ASCENDING") {
    buildSequenceByChannel(CH_BLUE_NORM, true, targetSequence);
    currentRuleHint = "Azul Crescente (menor->maior)";
  } else if (r == "BLUE_DESCENDING") {
    buildSequenceByChannel(CH_BLUE_NORM, false, targetSequence);
    currentRuleHint = "Azul Decresc. (maior->menor)";
  } else if (r == "GREEN_ASCENDING") {
    buildSequenceByChannel(CH_GREEN_NORM, true, targetSequence);
    currentRuleHint = "Verde Crescente (menor->maior)";
  } else if (r == "GREEN_DESCENDING") {
    buildSequenceByChannel(CH_GREEN_NORM, false, targetSequence);
    currentRuleHint = "Verde Decresc. (maior->menor)";
  } else if (r == "RED_ASCENDING") {
    buildSequenceByChannel(CH_RED_NORM, true, targetSequence);
    currentRuleHint = "Verm. Crescente (menor->maior)";
  } else if (r == "RED_DESCENDING") {
    buildSequenceByChannel(CH_RED_NORM, false, targetSequence);
    currentRuleHint = "Verm. Decresc. (maior->menor)";
  } else if (r == "CLEAR_ASCENDING") {
    buildSequenceByChannel(CH_CLEAR_RAW, true, targetSequence);
    currentRuleHint = "Brilho Cresc. (escuro->claro)";
  } else if (r == "CLEAR_DESCENDING") {
    buildSequenceByChannel(CH_CLEAR_RAW, false, targetSequence);
    currentRuleHint = "Brilho Decresc. (claro->escuro)";
  } else {
    // Fallback: se receber digitos numericos, usa permutacao senha % 24
    int idx = passwordToPermutationIndex(r.c_str());
    if (idx < 0) idx = 0;
    indexToPermutation((uint8_t)idx, targetSequence);
    currentRuleHint = "Senha " + r + " (mod24=" + String(idx) + ")";
  }

  // Imprime tabela completa de diagnostico no Serial para conferencia
  Serial.println("\n========== REGRA ATIVA ==========");
  Serial.println("Codigo recebido : " + r);
  Serial.println("Dica exibida    : " + currentRuleHint);
  Serial.println("Valores calibrados dos cartoes:");
  for (uint8_t i = 0; i < CARD_COUNT; i++) {
    float rn = getCardMetric(referenceCards[i], CH_RED_NORM);
    float gn = getCardMetric(referenceCards[i], CH_GREEN_NORM);
    float bn = getCardMetric(referenceCards[i], CH_BLUE_NORM);
    Serial.printf(
      "  ID %u (%-8s) -> Rn:%.3f | Gn:%.3f | Bn:%.3f | Clear:%u\n",
      i + 1, CARD_NAMES[i], rn, gn, bn, referenceCards[i].clear
    );
  }
  Serial.print("Sequencia alvo  : ");
  for (uint8_t i = 0; i < CARD_COUNT; i++) {
    uint8_t id = targetSequence[i];
    Serial.printf("%u (%s)", id, CARD_NAMES[id - 1]);
    if (i < CARD_COUNT - 1) Serial.print(" -> ");
  }
  Serial.println("\n=================================\n");
}

// =====================================================
// INTERFACE GRAFICA NO DISPLAY (240x135)
// =====================================================

void drawHeader(const char *subtitle, uint16_t color = C_CYAN) {
  tft.fillScreen(C_BLACK);
  tft.setTextWrap(false);

  tft.setTextSize(2);
  tft.setTextColor(color);
  tft.setCursor(8, 5);
  tft.print("COFRE CROMATICO");

  tft.drawFastHLine(8, 25, 224, C_DARKGREY);

  if (subtitle && strlen(subtitle) > 0) {
    tft.setTextSize(1);
    tft.setTextColor(C_WHITE);
    tft.setCursor(8, 30);
    tft.print(subtitle);
  }
}

void drawCardSlots(const uint8_t slots[CARD_COUNT], uint8_t filledCount) {
  const int16_t startX = 8;
  const int16_t startY = 68;
  const int16_t boxW   = 50;
  const int16_t boxH   = 38;
  const int16_t gap    = 8;

  for (uint8_t i = 0; i < CARD_COUNT; i++) {
    int16_t x = startX + i * (boxW + gap);

    if (i < filledCount && slots[i] >= 1 && slots[i] <= 4) {
      uint8_t id = slots[i];
      uint16_t bg = CARD_UI_COLORS[id - 1];
      uint16_t fg = (id == 2 || id == 3) ? C_BLACK : C_WHITE;

      tft.fillRoundRect(x, startY, boxW, boxH, 5, bg);
      tft.drawRoundRect(x, startY, boxW, boxH, 5, C_WHITE);

      tft.setTextSize(2);
      tft.setTextColor(fg);
      tft.setCursor(x + 14, startY + 11);
      tft.print(CARD_SHORT[id - 1]);
    } else {
      tft.drawRoundRect(x, startY, boxW, boxH, 5, C_DARKGREY);
      tft.setTextSize(1);
      tft.setTextColor(C_DARKGREY);
      tft.setCursor(x + 22, startY + 15);
      tft.print(i + 1);
    }
  }
}

void showStatusPopup(
  const char *title,
  const String &line1,
  const String &line2,
  uint16_t color = C_CYAN
) {
  drawHeader(title, color);

  tft.setTextSize(1);
  tft.setTextColor(C_WHITE);
  tft.setCursor(8, 54);
  tft.print(line1);

  tft.setCursor(8, 74);
  tft.print(line2);
}

void showRegisterScreen() {
  drawHeader("FASE 1: CALIBRAR CARTOES", C_CYAN);

  tft.setTextSize(1);
  tft.setTextColor(CARD_UI_COLORS[registeredCount]);
  tft.setCursor(8, 48);
  tft.printf("Apresente %u/4: %s", registeredCount + 1, CARD_NAMES[registeredCount]);

  uint8_t regPreview[CARD_COUNT] = {1, 2, 3, 4};
  drawCardSlots(regPreview, registeredCount);

  tft.setTextSize(1);
  tft.setTextColor(C_YELLOW);
  tft.setCursor(8, 116);
  tft.print("A: gravar cor");

  if (registeredCount > 0) {
    tft.setTextColor(C_DARKGREY);
    tft.setCursor(130, 116);
    tft.print("B: zerar");
  }

  Serial.printf(
    "[TELA] Aguardando cadastro %u/4 (%s). Aperte Botao A.\n",
    registeredCount + 1,
    CARD_NAMES[registeredCount]
  );
}

void showEnterScreen() {
  String sub = "REGRA: " + activeRuleCode;
  drawHeader(sub.c_str(), C_CYAN);

  // Linha de dica traduzida logo acima dos cartoes
  tft.setTextSize(1);
  tft.setTextColor(C_YELLOW);
  tft.setCursor(8, 46);
  tft.print(currentRuleHint);

  drawCardSlots(enteredSequence, enteredCount);

  tft.setTextSize(1);
  if (enteredCount < CARD_COUNT) {
    tft.setTextColor(C_GREEN);
    tft.setCursor(8, 116);
    tft.printf("A: ler %uo cartao", enteredCount + 1);

    if (enteredCount > 0) {
      tft.setTextColor(C_ORANGE);
      tft.setCursor(138, 116);
      tft.print("B: limpar");
    }
  } else {
    tft.setTextColor(C_GREEN);
    tft.setCursor(8, 116);
    tft.print("4/4 lidos! Aperte B p/ abrir!");
  }
}

void showResultScreen(bool unlocked) {
  if (unlocked) {
    drawHeader("COFRE DESBLOQUEADO!", C_GREEN);
    tft.setTextSize(1);
    tft.setTextColor(C_WHITE);
    tft.setCursor(8, 46);
    tft.printf("Sucesso em %u tentativa(s)!", attempts);
  } else {
    drawHeader("SENHA INCORRETA!", C_RED);
    tft.setTextSize(1);
    tft.setTextColor(C_WHITE);
    tft.setCursor(8, 46);
    tft.printf("Tentativa #%u falhou!", attempts);
  }

  // Exibe os 4 cartoes da tentativa recem-validada
  drawCardSlots(enteredSequence, CARD_COUNT);

  tft.setTextSize(1);
  tft.setTextColor(C_YELLOW);
  tft.setCursor(8, 116);
  if (unlocked) {
    tft.print("A: prox. regra | B: recalibrar");
  } else {
    tft.print("A: tentar de novo | B: recalib");
  }
}

// =====================================================
// LEITURA E COMPARACAO DE CORES (APDS-9960)
// =====================================================

bool readColor(ColorSample &result) {
  if (!sensorReady) return false;

  uint32_t sumR = 0, sumG = 0, sumB = 0, sumC = 0;

  for (uint8_t i = 0; i < SAMPLES_PER_READING; i++) {
    uint16_t r = 0, g = 0, b = 0, c = 0;

    bool okR = colorSensor.readRedLight(r);
    bool okG = colorSensor.readGreenLight(g);
    bool okB = colorSensor.readBlueLight(b);
    bool okC = colorSensor.readAmbientLight(c);

    if (!okR || !okG || !okB || !okC) {
      Serial.println("[ERRO] Falha ao ler canais do APDS-9960.");
      return false;
    }

    sumR += r;
    sumG += g;
    sumB += b;
    sumC += c;

    delay(SENSOR_SAMPLE_DELAY_MS);
  }

  result.r = (float)sumR / SAMPLES_PER_READING;
  result.g = (float)sumG / SAMPLES_PER_READING;
  result.b = (float)sumB / SAMPLES_PER_READING;
  result.clear = (uint16_t)(sumC / SAMPLES_PER_READING);

  float total = result.r + result.g + result.b;

  if (total <= 0.0f) {
    Serial.println("[AVISO] Leitura sem sinal RGB.");
    return false;
  }

  Serial.printf(
    "[SENSOR] Bruto -> R:%.1f G:%.1f B:%.1f C:%u | Norm -> Rn:%.3f Gn:%.3f Bn:%.3f\n",
    result.r, result.g, result.b, result.clear,
    result.r / total, result.g / total, result.b / total
  );

  return true;
}

float colorDistance(const ColorSample &a, const ColorSample &b) {
  float totalA = a.r + a.g + a.b;
  float totalB = b.r + b.g + b.b;

  if (totalA <= 0.0f || totalB <= 0.0f) {
    return 999.0f;
  }

  float dr = (a.r / totalA) - (b.r / totalB);
  float dg = (a.g / totalA) - (b.g / totalB);
  float db = (a.b / totalA) - (b.b / totalB);

  return sqrtf(dr * dr + dg * dg + db * db);
}

uint8_t identifyCard(const ColorSample &sample) {
  float bestDistance = 999.0f;
  uint8_t bestId = 0;

  Serial.println("--- Comparando com referencias ---");
  for (uint8_t i = 0; i < registeredCount; i++) {
    float distance = colorDistance(sample, referenceCards[i]);
    Serial.printf("  Dist para ID %u (%s): %.4f\n", i + 1, CARD_NAMES[i], distance);

    if (distance < bestDistance) {
      bestDistance = distance;
      bestId = i + 1;
    }
  }

  Serial.printf(
    "=> Melhor candidato: %u (%s) | Distancia: %.4f (Max: %.4f)\n",
    bestId,
    (bestId > 0) ? CARD_NAMES[bestId - 1] : "Nenhum",
    bestDistance,
    MAX_COLOR_DISTANCE
  );

  if (bestDistance <= MAX_COLOR_DISTANCE) {
    return bestId;
  }

  return 0;
}

// =====================================================
// CONTROLE DO JOGO
// =====================================================

void resetEnteredSequence() {
  enteredCount = 0;
  memset(enteredSequence, 0, sizeof(enteredSequence));
}

void resetCalibration() {
  registeredCount = 0;
  attempts = 0;
  resetEnteredSequence();
  state = STATE_REGISTERING;
  Serial.println("\n[SISTEMA] Calibracao reiniciada.");
  showRegisterScreen();
}

bool sequenceContains(uint8_t id) {
  for (uint8_t i = 0; i < enteredCount; i++) {
    if (enteredSequence[i] == id) return true;
  }
  return false;
}

void registerCurrentCard() {
  if (registeredCount >= CARD_COUNT) return;

  showStatusPopup(
    "LENDO CARTAO...",
    String("Gravando: ") + CARD_NAMES[registeredCount],
    "Mantenha o cartao parado...",
    CARD_UI_COLORS[registeredCount]
  );

  ColorSample sample;
  if (!readColor(sample)) {
    showStatusPopup("LEITURA INVALIDA", "Verifique luz/distancia", "Tente novamente com A", C_RED);
    delay(1200);
    showRegisterScreen();
    return;
  }

  for (uint8_t i = 0; i < registeredCount; i++) {
    float distance = colorDistance(sample, referenceCards[i]);
    if (distance < MIN_CARD_SEPARATION) {
      showStatusPopup(
        "COR MUITO PARECIDA!",
        String("Conflito com ") + CARD_NAMES[i],
        "Dist: " + String(distance, 3),
        C_ORANGE
      );
      Serial.printf("[REJEITADO] Conflito com %s (Dist=%.4f)\n", CARD_NAMES[i], distance);
      delay(1500);
      showRegisterScreen();
      return;
    }
  }

  referenceCards[registeredCount] = sample;
  registeredCount++;

  Serial.printf("[CADASTRO OK] Cartao %u (%s) salvo!\n", registeredCount, CARD_NAMES[registeredCount - 1]);

  if (registeredCount == CARD_COUNT) {
    // Agora que os 4 cartoes tem valores RGB reais, calcula a sequencia pela regra ativa!
    activeRuleCode = MOCK_RULES[currentRuleIndex];
    applyActiveRule(activeRuleCode);

    state = STATE_ENTERING;
    attempts = 0;
    resetEnteredSequence();

    showStatusPopup("CALIBRACAO OK!", "Regra: " + activeRuleCode, currentRuleHint, C_GREEN);
    delay(1500);
    showEnterScreen();
  } else {
    showRegisterScreen();
  }
}

void captureSequenceCard() {
  if (enteredCount >= CARD_COUNT) {
    showStatusPopup("4 CARTOES LIDOS!", "Aperte o BOTAO B (direita)", "para validar a sequencia!", C_YELLOW);
    delay(1300);
    showEnterScreen();
    return;
  }

  showStatusPopup(
    "IDENTIFICANDO...",
    String("Lendo posicao ") + String(enteredCount + 1) + " de 4",
    "Mantenha parado no sensor",
    C_CYAN
  );

  ColorSample sample;
  if (!readColor(sample)) {
    showStatusPopup("LEITURA INVALIDA", "Aproxime melhor o cartao", "e tente novamente", C_RED);
    delay(1200);
    showEnterScreen();
    return;
  }

  uint8_t id = identifyCard(sample);

  if (id == 0) {
    showStatusPopup("NAO RECONHECIDO", "Cor fora da margem salva", "Confira a luz/distancia", C_ORANGE);
    delay(1300);
    showEnterScreen();
    return;
  }

  if (sequenceContains(id)) {
    showStatusPopup(
      "CARTAO REPETIDO!",
      String(CARD_NAMES[id - 1]) + " ja foi inserido",
      "Apresente outra cor",
      C_ORANGE
    );
    delay(1200);
    showEnterScreen();
    return;
  }

  enteredSequence[enteredCount] = id;
  enteredCount++;

  Serial.printf("[SEQUENCIA] Posicao %u -> ID %u (%s)\n", enteredCount, id, CARD_NAMES[id - 1]);
  showEnterScreen();
}

void validateSequence() {
  if (enteredCount < CARD_COUNT) {
    if (enteredCount > 0) {
      Serial.println("[SEQUENCIA] Entrada parcial limpa pelo usuario.");
      resetEnteredSequence();
      showEnterScreen();
    }
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
    Serial.printf("\n[SUCESSO] Cofre DESBLOQUEADO (%s) em %u tentativa(s)!\n", activeRuleCode.c_str(), attempts);
    showResultScreen(true);
  } else {
    state = STATE_ERROR;
    Serial.printf("\n[FALHA] Combinacao incorreta na tentativa #%u.\n", attempts);
    showResultScreen(false);
    resetEnteredSequence();
  }
}

// =====================================================
// SETUP E LOOP PRINCIPAL
// =====================================================

void setup() {
  Serial.begin(115200);
  delay(250);

  pinMode(BTN_A_PIN, INPUT_PULLUP);
  pinMode(BTN_B_PIN, INPUT);

  pinMode(TFT_BL_PIN, OUTPUT);
  digitalWrite(TFT_BL_PIN, HIGH);

  tftSPI.begin(TFT_SCLK_PIN, -1, TFT_MOSI_PIN, TFT_CS_PIN);
  tft.init(135, 240);
  tft.setSPISpeed(40000000);
  tft.setRotation(1);

  tft.fillScreen(C_RED);   delay(100);
  tft.fillScreen(C_GREEN); delay(100);
  tft.fillScreen(C_BLUE);  delay(100);

  showStatusPopup("INICIALIZANDO...", "Comunicando com APDS-9960", "I2C: SDA=21 | SCL=22", C_CYAN);

  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
  Wire.setClock(100000);

  sensorReady = colorSensor.init();
  if (sensorReady) {
    sensorReady = colorSensor.enableLightSensor(false);
  }

  if (!sensorReady) {
    Serial.println("[ERRO CRITICO] APDS-9960 nao encontrado!");
    showStatusPopup("ERRO NO SENSOR", "Verifique SDA(21) e SCL(22)", "Reinicie a placa", C_RED);
    while (true) delay(1000);
  }

  Serial.println("APDS-9960 inicializado corretamente!");
  showRegisterScreen();
}

void loop() {
  bool clickA = checkButtonClick(btnA, "BOTAO A");
  bool clickB = checkButtonClick(btnB, "BOTAO B");

  if (clickA) {
    switch (state) {
      case STATE_REGISTERING:
        registerCurrentCard();
        break;

      case STATE_ENTERING:
        captureSequenceCard();
        break;

      case STATE_ERROR:
        // Mantem a mesma regra e tenta de novo
        state = STATE_ENTERING;
        resetEnteredSequence();
        showEnterScreen();
        break;

      case STATE_SUCCESS:
        // Avanca para a proxima regra da lista sem precisar recalibrar!
        currentRuleIndex = (currentRuleIndex + 1) % MOCK_RULES_COUNT;
        activeRuleCode = MOCK_RULES[currentRuleIndex];
        applyActiveRule(activeRuleCode);
        attempts = 0;
        resetEnteredSequence();
        state = STATE_ENTERING;
        showEnterScreen();
        break;
    }
  }

  if (clickB) {
    switch (state) {
      case STATE_REGISTERING:
        if (registeredCount > 0) resetCalibration();
        break;

      case STATE_ENTERING:
        validateSequence();
        break;

      case STATE_ERROR:
      case STATE_SUCCESS:
        resetCalibration();
        break;
    }
  }

  delay(10);
}
