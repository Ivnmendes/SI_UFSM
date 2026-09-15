#include <SoftwareSerial.h>
#include <string.h>

// ============================================================
// CONFIGURAÇÃO
// ============================================================

SoftwareSerial serialLink(10, 11); // RX, TX

const uint8_t SOF = 0xAA;

// Tipos de mensagem
const uint8_t TYPE_BYTE  = 0x01;
const uint8_t TYPE_WORD  = 0x02;
const uint8_t TYPE_FLOAT = 0x03;
const uint8_t TYPE_DATA  = 0x04;

// Controle
const uint8_t TYPE_ACK  = 0x10;
const uint8_t TYPE_NACK = 0x11;

const uint16_t MAX_PAYLOAD = 128;
const unsigned long TIMEOUT_MS = 500;
const uint8_t MAX_RETRIES = 3;


// ============================================================
// VARIÁVEIS DO PROTOCOLO
// ============================================================

uint8_t sequence = 0;

bool hasReceivedSequence = false;
uint8_t lastReceivedSequence = 0;

// Controle de ACK/NACK
bool responseReceived = false;
bool responseAccepted = false;
uint8_t responseSequence = 0;

// Simulação de falhas
bool corruptNextFrame = false;
bool dropNextAck = false;


// ============================================================
// PARSER
// ============================================================

enum ParserState {
  WAIT_SOF,
  READ_TYPE,
  READ_SEQUENCE,
  READ_SIZE_LOW,
  READ_SIZE_HIGH,
  READ_PAYLOAD,
  READ_CRC_LOW,
  READ_CRC_HIGH
};

ParserState parserState = WAIT_SOF;

uint8_t receivedType;
uint8_t receivedSequence;
uint16_t receivedSize;
uint16_t receivedPayloadIndex;

uint8_t receivedPayload[MAX_PAYLOAD];

uint16_t receivedCrc;


// ============================================================
// CRC-16-CCITT
// ============================================================

void updateCRC(uint16_t &crc, uint8_t value)
{
  crc ^= ((uint16_t)value << 8);

  for (uint8_t i = 0; i < 8; i++) {

    if (crc & 0x8000) {
      crc = (crc << 1) ^ 0x1021;
    }
    else {
      crc <<= 1;
    }
  }
}


uint16_t calculateCRC(
  uint8_t type,
  uint8_t seq,
  uint16_t size,
  const uint8_t *payload
)
{
  uint16_t crc = 0xFFFF;

  updateCRC(crc, type);
  updateCRC(crc, seq);

  updateCRC(crc, size & 0xFF);
  updateCRC(crc, (size >> 8) & 0xFF);

  for (uint16_t i = 0; i < size; i++) {
    updateCRC(crc, payload[i]);
  }

  return crc;
}


// ============================================================
// RESET DO PARSER
// ============================================================

void resetParser()
{
  parserState = WAIT_SOF;

  receivedType = 0;
  receivedSequence = 0;
  receivedSize = 0;
  receivedPayloadIndex = 0;
  receivedCrc = 0;
}


// ============================================================
// ENVIO DE ACK
// ============================================================

void sendAck(uint8_t seq)
{
  // Simula perda de ACK
  if (dropNextAck) {
    dropNextAck = false;

    Serial.println("[TESTE] ACK perdido propositalmente.");

    return;
  }

  uint16_t crc = calculateCRC(
    TYPE_ACK,
    seq,
    0,
    nullptr
  );

  serialLink.write(SOF);
  serialLink.write(TYPE_ACK);
  serialLink.write(seq);

  serialLink.write(0);
  serialLink.write(0);

  serialLink.write(crc & 0xFF);
  serialLink.write((crc >> 8) & 0xFF);

  serialLink.flush();
}


// ============================================================
// ENVIO DE NACK
// ============================================================

void sendNack(uint8_t seq)
{
  uint16_t crc = calculateCRC(
    TYPE_NACK,
    seq,
    0,
    nullptr
  );

  serialLink.write(SOF);
  serialLink.write(TYPE_NACK);
  serialLink.write(seq);

  serialLink.write(0);
  serialLink.write(0);

  serialLink.write(crc & 0xFF);
  serialLink.write((crc >> 8) & 0xFF);

  serialLink.flush();
}


// ============================================================
// PROCESSAMENTO DE QUADRO RECEBIDO
// ============================================================

void processFrame()
{
  uint16_t calculatedCRC = calculateCRC(
    receivedType,
    receivedSequence,
    receivedSize,
    receivedPayload
  );

  // ----------------------------------------------------------
  // CRC INCORRETO
  // ----------------------------------------------------------

  if (calculatedCRC != receivedCrc) {

    Serial.println("ERRO: CRC invalido.");

    sendNack(receivedSequence);

    return;
  }


  // ----------------------------------------------------------
  // ACK / NACK
  // ----------------------------------------------------------

  if (
    receivedType == TYPE_ACK ||
    receivedType == TYPE_NACK
  ) {

    if (receivedSize != 0) {
      return;
    }

    responseReceived = true;

    responseAccepted =
      (receivedType == TYPE_ACK);

    responseSequence =
      receivedSequence;

    return;
  }


  // ----------------------------------------------------------
  // MENSAGEM DUPLICADA
  // ----------------------------------------------------------

  if (
    hasReceivedSequence &&
    receivedSequence == lastReceivedSequence
  ) {

    Serial.println("Mensagem duplicada detectada.");

    sendAck(receivedSequence);

    return;
  }


  // ----------------------------------------------------------
  // VALIDACAO DOS TAMANHOS
  // ----------------------------------------------------------

  if (
    receivedType == TYPE_BYTE &&
    receivedSize != 1
  ) {
    sendNack(receivedSequence);
    return;
  }

  if (
    receivedType == TYPE_WORD &&
    receivedSize != 2
  ) {
    sendNack(receivedSequence);
    return;
  }

  if (
    receivedType == TYPE_FLOAT &&
    receivedSize != sizeof(float)
  ) {
    sendNack(receivedSequence);
    return;
  }


  // ----------------------------------------------------------
  // PROCESSAMENTO
  // ----------------------------------------------------------

  switch (receivedType) {

    case TYPE_BYTE:

      Serial.print("BYTE recebido: ");
      Serial.println(receivedPayload[0]);

      break;


    case TYPE_WORD:
    {
      uint16_t value =
        (uint16_t)receivedPayload[0] |
        ((uint16_t)receivedPayload[1] << 8);

      Serial.print("WORD recebido: ");
      Serial.println(value);

      break;
    }


    case TYPE_FLOAT:
    {
      float value;

      memcpy(
        &value,
        receivedPayload,
        sizeof(float)
      );

      Serial.print("FLOAT recebido: ");
      Serial.println(value, 5);

      break;
    }


    case TYPE_DATA:

      Serial.print("DATA recebida: ");

      for (uint16_t i = 0; i < receivedSize; i++) {
        Serial.write(receivedPayload[i]);
      }

      Serial.println();

      break;


    default:

      Serial.println("Tipo de mensagem desconhecido.");

      sendNack(receivedSequence);

      return;
  }


  // ----------------------------------------------------------
  // MENSAGEM RECEBIDA COM SUCESSO
  // ----------------------------------------------------------

  hasReceivedSequence = true;
  lastReceivedSequence = receivedSequence;

  sendAck(receivedSequence);
}


// ============================================================
// PARSER
// ============================================================

void processByte(uint8_t value)
{
  switch (parserState) {

    case WAIT_SOF:

      if (value == SOF) {
        parserState = READ_TYPE;
      }

      break;


    case READ_TYPE:

      receivedType = value;

      parserState = READ_SEQUENCE;

      break;


    case READ_SEQUENCE:

      receivedSequence = value;

      parserState = READ_SIZE_LOW;

      break;


    case READ_SIZE_LOW:

      receivedSize = value;

      parserState = READ_SIZE_HIGH;

      break;


    case READ_SIZE_HIGH:

      receivedSize |= ((uint16_t)value << 8);

      receivedPayloadIndex = 0;

      if (receivedSize > MAX_PAYLOAD) {

        Serial.println("ERRO: payload muito grande.");

        resetParser();

        break;
      }

      if (receivedSize == 0) {
        parserState = READ_CRC_LOW;
      }
      else {
        parserState = READ_PAYLOAD;
      }

      break;


    case READ_PAYLOAD:

      receivedPayload[
        receivedPayloadIndex++
      ] = value;

      if (receivedPayloadIndex >= receivedSize) {
        parserState = READ_CRC_LOW;
      }

      break;


    case READ_CRC_LOW:

      receivedCrc = value;

      parserState = READ_CRC_HIGH;

      break;


    case READ_CRC_HIGH:

      receivedCrc |= ((uint16_t)value << 8);

      processFrame();

      resetParser();

      break;
  }
}


// ============================================================
// ATUALIZAÇÃO DA COMUNICAÇÃO
// ============================================================

void updateProtocol()
{
  while (serialLink.available()) {

    uint8_t value = serialLink.read();

    processByte(value);
  }
}


// ============================================================
// ESPERA ACK/NACK
// ============================================================

bool waitForResponse(uint8_t expectedSequence)
{
  responseReceived = false;
  responseAccepted = false;
  responseSequence = 0;

  unsigned long startTime = millis();

  while (
    millis() - startTime <
    TIMEOUT_MS
  ) {

    while (serialLink.available()) {

      uint8_t value =
        serialLink.read();

      processByte(value);

      if (
        responseReceived &&
        responseSequence ==
        expectedSequence
      ) {

        return responseAccepted;
      }
    }
  }

  Serial.println("TIMEOUT: nenhum ACK/NACK recebido.");

  return false;
}


// ============================================================
// ENVIO DE QUADRO
// ============================================================

bool sendFrame(
  uint8_t type,
  const uint8_t *payload,
  uint16_t size
)
{
  if (size > MAX_PAYLOAD) {
    return false;
  }

  uint8_t currentSequence =
    sequence++;

  uint16_t crc =
    calculateCRC(
      type,
      currentSequence,
      size,
      payload
    );


  for (
    uint8_t attempt = 0;
    attempt < MAX_RETRIES;
    attempt++
  ) {

    Serial.print("Tentativa ");
    Serial.print(attempt + 1);
    Serial.print("/");
    Serial.println(MAX_RETRIES);


    // --------------------------------------------------------
    // SOF
    // --------------------------------------------------------

    serialLink.write(SOF);


    // --------------------------------------------------------
    // TYPE
    // --------------------------------------------------------

    serialLink.write(type);


    // --------------------------------------------------------
    // SEQUENCE
    // --------------------------------------------------------

    serialLink.write(currentSequence);


    // --------------------------------------------------------
    // SIZE
    // --------------------------------------------------------

    serialLink.write(size & 0xFF);
    serialLink.write((size >> 8) & 0xFF);


    // --------------------------------------------------------
    // PAYLOAD
    // --------------------------------------------------------

    for (uint16_t i = 0; i < size; i++) {
      serialLink.write(payload[i]);
    }


    // --------------------------------------------------------
    // CRC
    // --------------------------------------------------------

    uint16_t frameCrc = crc;

    // Erro proposital apenas na primeira tentativa
    if (
      corruptNextFrame &&
      attempt == 0
    ) {

      frameCrc ^= 0xFFFF;

      corruptNextFrame = false;

      Serial.println(
        "[TESTE] CRC corrompido propositalmente."
      );
    }

    serialLink.write(frameCrc & 0xFF);
    serialLink.write((frameCrc >> 8) & 0xFF);

    serialLink.flush();


    // --------------------------------------------------------
    // AGUARDA RESPOSTA
    // --------------------------------------------------------

    if (
      waitForResponse(
        currentSequence
      )
    ) {

      Serial.println(
        "SUCESSO: mensagem confirmada."
      );

      return true;
    }

    Serial.println(
      "Falha na tentativa."
    );
  }


  Serial.println(
    "ERRO: numero maximo de tentativas atingido."
  );

  return false;
}


// ============================================================
// FUNCOES EXIGIDAS PELO TRABALHO
// ============================================================

bool sendByte(uint8_t value)
{
  return sendFrame(
    TYPE_BYTE,
    &value,
    1
  );
}


bool sendWord(uint16_t value)
{
  uint8_t payload[2];

  payload[0] =
    value & 0xFF;

  payload[1] =
    (value >> 8) & 0xFF;

  return sendFrame(
    TYPE_WORD,
    payload,
    2
  );
}


bool sendFloat(float value)
{
  uint8_t payload[sizeof(float)];

  memcpy(
    payload,
    &value,
    sizeof(float)
  );

  return sendFrame(
    TYPE_FLOAT,
    payload,
    sizeof(float)
  );
}


bool sendData(
  const uint8_t *data,
  uint16_t size
)
{
  if (
    data == nullptr ||
    size == 0 ||
    size > MAX_PAYLOAD
  ) {
    return false;
  }

  return sendFrame(
    TYPE_DATA,
    data,
    size
  );
}


// ============================================================
// SETUP
// ============================================================

void setup()
{
  Serial.begin(9600);

  serialLink.begin(9600);

  resetParser();

  Serial.println();
  Serial.println("==============================");
  Serial.println(" ARDUINO A - PROTOCOLO SERIAL");
  Serial.println("==============================");
  Serial.println();
  Serial.println("Comandos:");
  Serial.println("1 - Enviar BYTE");
  Serial.println("2 - Enviar WORD");
  Serial.println("3 - Enviar FLOAT");
  Serial.println("4 - Enviar DATA");
  Serial.println("5 - Testar erro de CRC");
  Serial.println();
}


// ============================================================
// LOOP
// ============================================================

void loop()
{
  updateProtocol();


  if (Serial.available()) {

    char command =
      Serial.read();


    switch (command) {

      case '1':
      {
        uint8_t value = 42;

        Serial.println();
        Serial.println(
          "Enviando BYTE = 42"
        );

        sendByte(value);

        break;
      }


      case '2':
      {
        uint16_t value = 1500;

        Serial.println();
        Serial.println(
          "Enviando WORD = 1500"
        );

        sendWord(value);

        break;
      }


      case '3':
      {
        float value = 3.14159;

        Serial.println();
        Serial.println(
          "Enviando FLOAT = 3.14159"
        );

        sendFloat(value);

        break;
      }


      case '4':
      {
        const char message[] =
          "Ola! Esta e uma DATA de tamanho variavel.";

        Serial.println();
        Serial.println(
          "Enviando DATA..."
        );

        sendData(
          (const uint8_t *)message,
          strlen(message) + 1
        );

        break;
      }


      case '5':
      {
        Serial.println();
        Serial.println(
          "Teste de erro de CRC."
        );

        corruptNextFrame = true;

        uint8_t value = 99;

        sendByte(value);

        break;
      }
    }
  }
}