#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <math.h>
#include <string.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <SparkFun_APDS9960.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

// =====================================================
// DEFINICOES DE REDE E MQTT (RFC 001 - Grupo 7)
// =====================================================

#define MODULO_ID   "7"
#define MODULO_NUM  7

const char* WIFI_SSID     = "iot2022";
const char* WIFI_PASSWORD = "S3nhab0@";
const char* MQTT_BROKER   = "192.168.2.100";
const int   MQTT_PORT     = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

// Variáveis de estado global sincronizadas pela Central
char serialBomba[8]   = "-----";
int  tempoRestante    = 0;
bool jogoRodando      = false;
bool minhaVez         = false;
bool jaResolvido      = false;

// Variáveis para detecção e armazenamento de dicas recebidas
bool temDicaNova      = false;
int  grupoOrigemDica  = 0;
char conteudoDica[64] = "Aguardando dica...";

// =====================================================
// PINOS DA TTGO T-DISPLAY ORIGINAL (ESP32)
// =====================================================

constexpr uint8_t BTN_A_PIN = 0;   // Botao esquerdo (pull-up interno)
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
// CONFIGURACOES DO JOGO E REGRAS
// =====================================================

constexpr uint8_t CARD_COUNT = 4;
constexpr uint8_t PERMUTATION_COUNT = 24;
constexpr uint8_t SAMPLES_PER_READING = 8;

constexpr float MAX_COLOR_DISTANCE = 0.16f;
constexpr float MIN_CARD_SEPARATION = 0.06f;

constexpr uint32_t DEBOUNCE_MS = 50;
constexpr uint16_t SENSOR_SAMPLE_DELAY_MS = 80;

String activeRuleCode = "PADRAO";
String currentRuleHint = "Aguardando dica...";

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

// Declarações antecipadas
void showRegisterScreen();
void showEnterScreen();
void showResultScreen(bool unlocked);
void showStatusPopup(const char *title, const String &line1, const String &line2, uint16_t color);
void applyActiveRule(const String &ruleStr);

void callbackMqtt(char* topic, byte* payload, unsigned int length) {
  char msg[length + 1];
  memcpy(msg, payload, length);
  msg[length] = '\0';

  // Higieniza quebras de linha residuais
  while (length > 0 && (msg[length - 1] == '\r' || msg[length - 1] == '\n' || msg[length - 1] == ' ')) {
    msg[--length] = '\0';
  }

  Serial.printf("[MQTT] Mensagem em [%s]: %s\n", topic, msg);

  // 1. Estado Global da Partida
  if (strcmp(topic, "jogo/estado") == 0) {
    if (strcmp(msg, "START") == 0) {
      jogoRodando = true;
      jaResolvido = false;
      temDicaNova = false;
      attempts = 0;
      Serial.println("[JOGO] Partida iniciada pela Central!");
    } 
    else if (strcmp(msg, "RESET") == 0) {
      jogoRodando = false;
      minhaVez    = false;
      jaResolvido = false;
      temDicaNova = false;
      Serial.println("[JOGO] Partida resetada.");
    } 
    else if (strcmp(msg, "VICTORY") == 0 || strcmp(msg, "DEFEAT") == 0) {
      jogoRodando = false;
      minhaVez    = false;
      Serial.println("[JOGO] Partida encerrada.");
    }
  }

  else if (strcmp(topic, "jogo/modulo/ativo") == 0) {
    int idAtivo = atoi(msg);
    minhaVez = (idAtivo == MODULO_NUM);
    Serial.printf("[TURNO] Módulo ativo: %d (Minha vez? %s)\n", idAtivo, minhaVez ? "SIM" : "NAO");
  }

  else if (strcmp(topic, "jogo/serial") == 0) {
    strncpy(serialBomba, msg, sizeof(serialBomba));
    Serial.printf("[SERIAL] Bomba SN: %s\n", serialBomba);
  }

  else if (strcmp(topic, "jogo/tempo") == 0) {
    tempoRestante = atoi(msg);
  }

  else {
    int idOrigem = 0;
    int pos = 0;
    if (sscanf(topic, "jogo/modulo/" MODULO_ID "/dica/%d%n", &idOrigem, &pos) == 1 && topic[pos] == '\0') {
      grupoOrigemDica = idOrigem;
      strncpy(conteudoDica, msg, sizeof(conteudoDica) - 1);
      conteudoDica[sizeof(conteudoDica) - 1] = '\0';
      temDicaNova = true;
      
      Serial.printf("[DICA] Recebida do Grupo %d: %s\n", grupoOrigemDica, conteudoDica);

      // Aplica a dica recebida imediatamente como regra de senha/sequencia!
      activeRuleCode = String(conteudoDica);
      if (registeredCount == CARD_COUNT) {
        applyActiveRule(activeRuleCode);
      }
    }
  }
}

void reconectarMQTT() {
  while (!client.connected()) {
    Serial.print("[MQTT] Conectando ao broker... ");
    if (client.connect("Modulo_" MODULO_ID,
                       "jogo/modulo/" MODULO_ID "/status",
                       0,
                       true,
                       "OFFLINE")) {
      
      Serial.println("Conectado!");
      client.publish("jogo/modulo/" MODULO_ID "/status", "ONLINE", true);

      // Inscrições oficiais + escuta de dicas direcionadas/roteadas
      client.subscribe("jogo/estado");
      client.subscribe("jogo/serial");
      client.subscribe("jogo/modulo/ativo");
      client.subscribe("jogo/modulo/" MODULO_ID "/dica/+");
      client.subscribe("jogo/tempo");
    } else {
      Serial.printf("Falha (rc=%d). Tentando em 1s...\n", client.state());
      delay(1000);
    }
  }
}

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

void buildSequenceByChannel(RuleChannel channel, bool ascending, uint8_t output[CARD_COUNT]) {
  uint8_t ids[CARD_COUNT] = {1, 2, 3, 4};
  float metrics[CARD_COUNT];

  for (uint8_t i = 0; i < CARD_COUNT; i++) {
    metrics[i] = getCardMetric(referenceCards[i], channel);
  }

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

void applyActiveRule(const String &ruleStr) {
  String r = ruleStr;
  r.trim();
  r.toUpperCase();

  if (r == "BLUE_ASCENDING") {
    buildSequenceByChannel(CH_BLUE_NORM, true, targetSequence);
    currentRuleHint = "Azul Crescente";
  } else if (r == "BLUE_DESCENDING") {
    buildSequenceByChannel(CH_BLUE_NORM, false, targetSequence);
    currentRuleHint = "Azul Decresc.";
  } else if (r == "GREEN_ASCENDING") {
    buildSequenceByChannel(CH_GREEN_NORM, true, targetSequence);
    currentRuleHint = "Verde Crescente";
  } else if (r == "GREEN_DESCENDING") {
    buildSequenceByChannel(CH_GREEN_NORM, false, targetSequence);
    currentRuleHint = "Verde Decresc.";
  } else if (r == "RED_ASCENDING") {
    buildSequenceByChannel(CH_RED_NORM, true, targetSequence);
    currentRuleHint = "Verm. Crescente";
  } else if (r == "RED_DESCENDING") {
    buildSequenceByChannel(CH_RED_NORM, false, targetSequence);
    currentRuleHint = "Verm. Decresc.";
  } else if (r == "CLEAR_ASCENDING") {
    buildSequenceByChannel(CH_CLEAR_RAW, true, targetSequence);
    currentRuleHint = "Brilho Cresc.";
  } else if (r == "CLEAR_DESCENDING") {
    buildSequenceByChannel(CH_CLEAR_RAW, false, targetSequence);
    currentRuleHint = "Brilho Decresc.";
  } else {
    int idx = passwordToPermutationIndex(r.c_str());
    if (idx < 0) idx = 0;
    indexToPermutation((uint8_t)idx, targetSequence);
    currentRuleHint = "Senha " + r;
  }
}

// =====================================================
// INTERFACE GRAFICA NO DISPLAY (240x135)
// =====================================================

void drawHeader(const char *subtitle, uint16_t color = C_CYAN) {
  tft.fillScreen(C_BLACK);
  tft.setTextWrap(false);

  tft.setTextSize(1);
  tft.setTextColor(C_YELLOW);
  tft.setCursor(8, 4);
  tft.printf("SN: %s | T: %ds", serialBomba, tempoRestante);

  tft.setTextSize(2);
  tft.setTextColor(color);
  tft.setCursor(8, 16);
  tft.print("COFRE CROMATICO");

  tft.drawFastHLine(8, 36, 224, C_DARKGREY);

  if (subtitle && strlen(subtitle) > 0) {
    tft.setTextSize(1);
    tft.setTextColor(minhaVez ? C_GREEN : C_ORANGE);
    tft.setCursor(8, 42);
    tft.print(subtitle);
  }
}

void drawCardSlots(const uint8_t slots[CARD_COUNT], uint8_t filledCount) {
  const int16_t startX = 8;
  const int16_t startY = 74;
  const int16_t boxW   = 50;
  const int16_t boxH   = 36;
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
      tft.setCursor(x + 14, startY + 10);
      tft.print(CARD_SHORT[id - 1]);
    } else {
      tft.drawRoundRect(x, startY, boxW, boxH, 5, C_DARKGREY);
      tft.setTextSize(1);
      tft.setTextColor(C_DARKGREY);
      tft.setCursor(x + 22, startY + 14);
      tft.print(i + 1);
    }
  }
}

void showStatusPopup(const char *title, const String &line1, const String &line2, uint16_t color = C_CYAN) {
  drawHeader(title, color);
  tft.setTextSize(1);
  tft.setTextColor(C_WHITE);
  tft.setCursor(8, 62);
  tft.print(line1);
  tft.setCursor(8, 82);
  tft.print(line2);
}

void showRegisterScreen() {
  if (!minhaVez) {
    showStatusPopup("AGUARDANDO TURNO...", "Outro grupo esta jogando.", "Aguarde sua vez...", C_ORANGE);
    return;
  }

  drawHeader("FASE 1: CALIBRAR CARTOES", C_CYAN);

  tft.setTextSize(1);
  tft.setTextColor(CARD_UI_COLORS[registeredCount]);
  tft.setCursor(8, 56);
  tft.printf("Apresente %u/4: %s", registeredCount + 1, CARD_NAMES[registeredCount]);

  uint8_t regPreview[CARD_COUNT] = {1, 2, 3, 4};
  drawCardSlots(regPreview, registeredCount);

  tft.setTextSize(1);
  tft.setTextColor(C_YELLOW);
  tft.setCursor(8, 118);
  tft.print("A: gravar");
  if (registeredCount > 0) {
    tft.setCursor(150, 118);
    tft.print("B: zerar");
  }
}

void showEnterScreen() {
  if (!minhaVez) {
    showStatusPopup("MODULO TRAVADO", "Nao e o seu turno atual.", "Aguarde a liberacao...", C_ORANGE);
    return;
  }

  String sub = temDicaNova ? "Dica G" + String(grupoOrigemDica) + ": " + String(conteudoDica) : currentRuleHint;
  drawHeader(sub.c_str(), C_CYAN);
  
  drawCardSlots(enteredSequence, enteredCount);

  tft.setTextSize(1);
  if (enteredCount < CARD_COUNT) {
    tft.setTextColor(C_GREEN);
    tft.setCursor(8, 118);
    tft.printf("A: ler %uo cartao", enteredCount + 1);
    if (enteredCount > 0) {
      tft.setTextColor(C_ORANGE);
      tft.setCursor(150, 118);
      tft.print("B: limpar");
    }
  } else {
    tft.setTextColor(C_GREEN);
    tft.setCursor(8, 118);
    tft.print("Aperte B p/ validar!");
  }
}

void showResultScreen(bool unlocked) {
  if (unlocked) {
    drawHeader("COFRE DESBLOQUEADO!", C_GREEN);
    tft.setTextSize(1);
    tft.setTextColor(C_WHITE);
    tft.setCursor(8, 56);
    tft.print("Desafio concluido com sucesso!");
  } else {
    drawHeader("SENHA INCORRETA!", C_RED);
    tft.setTextSize(1);
    tft.setTextColor(C_WHITE);
    tft.setCursor(8, 56);
    tft.printf("Strike! Tentativa #%u", attempts);
  }

  drawCardSlots(enteredSequence, CARD_COUNT);

  tft.setTextSize(1);
  tft.setTextColor(C_YELLOW);
  tft.setCursor(8, 118);
  tft.print(unlocked ? "Aguardando proximo..." : "A: tentar de novo");
}

bool readColor(ColorSample &result) {
  if (!sensorReady) return false;

  uint32_t sumR = 0, sumG = 0, sumB = 0, sumC = 0;

  for (uint8_t i = 0; i < SAMPLES_PER_READING; i++) {
    uint16_t r = 0, g = 0, b = 0, c = 0;
    if (!colorSensor.readRedLight(r) || !colorSensor.readGreenLight(g) ||
        !colorSensor.readBlueLight(b) || !colorSensor.readAmbientLight(c)) {
      return false;
    }
    sumR += r; sumG += g; sumB += b; sumC += c;
    delay(SENSOR_SAMPLE_DELAY_MS);
  }

  result.r = (float)sumR / SAMPLES_PER_READING;
  result.g = (float)sumG / SAMPLES_PER_READING;
  result.b = (float)sumB / SAMPLES_PER_READING;
  result.clear = (uint16_t)(sumC / SAMPLES_PER_READING);

  return (result.r + result.g + result.b) > 0.0f;
}

float colorDistance(const ColorSample &a, const ColorSample &b) {
  float totalA = a.r + a.g + a.b;
  float totalB = b.r + b.g + b.b;
  if (totalA <= 0.0f || totalB <= 0.0f) return 999.0f;

  float dr = (a.r / totalA) - (b.r / totalB);
  float dg = (a.g / totalA) - (b.g / totalB);
  float db = (a.b / totalA) - (b.b / totalB);
  return sqrtf(dr * dr + dg * dg + db * db);
}

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

void resetEnteredSequence() {
  enteredCount = 0;
  memset(enteredSequence, 0, sizeof(enteredSequence));
}

void resetCalibration() {
  registeredCount = 0;
  attempts = 0;
  resetEnteredSequence();
  state = STATE_REGISTERING;
  showRegisterScreen();
}

bool sequenceContains(uint8_t id) {
  for (uint8_t i = 0; i < enteredCount; i++) {
    if (enteredSequence[i] == id) return true;
  }
  return false;
}

void registerCurrentCard() {
  if (!minhaVez || registeredCount >= CARD_COUNT) return;

  showStatusPopup("LENDO CARTAO...", String("Gravando: ") + CARD_NAMES[registeredCount], "Mantenha parado...", CARD_UI_COLORS[registeredCount]);

  ColorSample sample;
  if (!readColor(sample)) {
    showStatusPopup("LEITURA INVALIDA", "Verifique luz/distancia", "Tente novamente com A", C_RED);
    delay(1000);
    showRegisterScreen();
    return;
  }

  for (uint8_t i = 0; i < registeredCount; i++) {
    if (colorDistance(sample, referenceCards[i]) < MIN_CARD_SEPARATION) {
      showStatusPopup("COR REJEITADA", "Muito parecida com outra", "Tente outra cor", C_ORANGE);
      delay(1200);
      showRegisterScreen();
      return;
    }
  }

  referenceCards[registeredCount] = sample;
  registeredCount++;

  if (registeredCount == CARD_COUNT) {
    applyActiveRule(activeRuleCode);
    state = STATE_ENTERING;
    resetEnteredSequence();

    showStatusPopup("CALIBRACAO OK!", "Aguardando insercao", currentRuleHint, C_GREEN);
    delay(1200);
    showEnterScreen();
  } else {
    showRegisterScreen();
  }
}

void captureSequenceCard() {
  if (!minhaVez) return;

  if (enteredCount >= CARD_COUNT) {
    showStatusPopup("4 CARTOES LIDOS!", "Aperte B p/ validar!", "", C_YELLOW);
    delay(1000);
    showEnterScreen();
    return;
  }

  showStatusPopup("IDENTIFICANDO...", String("Posicao ") + String(enteredCount + 1) + " de 4", "Mantenha parado", C_CYAN);

  ColorSample sample;
  if (!readColor(sample)) {
    showStatusPopup("LEITURA INVALIDA", "Aproxime melhor", "Tente novamente", C_RED);
    delay(1000);
    showEnterScreen();
    return;
  }

  uint8_t id = identifyCard(sample);
  if (id == 0) {
    showStatusPopup("NAO RECONHECIDO", "Cor fora do padrao", "Tente novamente", C_ORANGE);
    delay(1000);
    showEnterScreen();
    return;
  }

  if (sequenceContains(id)) {
    showStatusPopup("CARTAO REPETIDO", "Cada cor 1 unica vez", "Use outra cor", C_ORANGE);
    delay(1000);
    showEnterScreen();
    return;
  }

  enteredSequence[enteredCount] = id;
  enteredCount++;
  showEnterScreen();
}

void validateSequence() {
  if (!minhaVez) return;

  if (enteredCount < CARD_COUNT) {
    if (enteredCount > 0) {
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
    jaResolvido = true;
    client.publish("jogo/modulo/" MODULO_ID "/evento", "SOLVED");
    Serial.println("[EVENTO] Publicado: SOLVED");
    showResultScreen(true);
  } else {
    state = STATE_ERROR;
    client.publish("jogo/modulo/" MODULO_ID "/evento", "ERROR");
    Serial.println("[EVENTO] Publicado: ERROR (Strike)");
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

  tft.fillScreen(C_RED);   delay(80);
  tft.fillScreen(C_GREEN); delay(80);
  tft.fillScreen(C_BLUE);  delay(80);

  showStatusPopup("INICIALIZANDO...", "Conectando Wi-Fi & MQTT", "Protocolo RFC 001", C_CYAN);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  client.setServer(MQTT_BROKER, MQTT_PORT);
  client.setCallback(callbackMqtt);

  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
  Wire.setClock(100000);

  sensorReady = colorSensor.init();
  if (sensorReady) {
    sensorReady = colorSensor.enableLightSensor(false);
  }

  if (!sensorReady) {
    showStatusPopup("ERRO NO SENSOR", "Verifique SDA/SCL", "Reinicie a placa", C_RED);
    while (true) delay(1000);
  }

  showRegisterScreen();
}

void loop() {
  if (!client.connected()) {
    reconectarMQTT();
  }
  client.loop();

  static bool ultimoMinhaVez = false;
  static GameState ultimoEstado = STATE_REGISTERING;
  static bool ultimaDicaStatus = false;
  
  if (minhaVez != ultimoMinhaVez || state != ultimoEstado || temDicaNova != ultimaDicaStatus) {
    ultimoMinhaVez = minhaVez;
    ultimoEstado = state;
    ultimaDicaStatus = temDicaNova;
    
    if (state == STATE_REGISTERING) showRegisterScreen();
    else if (state == STATE_ENTERING) showEnterScreen();
  }

  bool clickA = checkButtonClick(btnA, "BOTAO A");
  bool clickB = checkButtonClick(btnB, "BOTAO B");

  if (clickA && jogoRodando && minhaVez && !jaResolvido) {
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

  if (clickB && jogoRodando && minhaVez && !jaResolvido) {
    if (state == STATE_REGISTERING) {
      if (registeredCount > 0) resetCalibration();
    } else if (state == STATE_ENTERING) {
      validateSequence();
    } else if (state == STATE_ERROR) {
      resetCalibration();
    }
  }

  delay(10);
}
