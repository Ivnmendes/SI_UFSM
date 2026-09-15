#include "ArduinoProtocol.h"
#include <string.h>

ArduinoProtocol::ArduinoProtocol(
    SoftwareSerial &serial,
    ByteCallback byteCallback,
    WordCallback wordCallback,
    FloatCallback floatCallback,
    DataCallback dataCallback
)
    : serial(serial),
      onByte(byteCallback),
      onWord(wordCallback),
      onFloat(floatCallback),
      onData(dataCallback),
      sequence(0),
      hasReceivedSequence(false),
      lastReceivedSequence(0),
      responseReceived(false),
      responseAccepted(false),
      responseSequence(0),
      corruptNextFrame(false),
      dropNextAck(false),
      parserState(WAIT_SOF),
      receivedType(0),
      receivedSequence(0),
      receivedSize(0),
      receivedPayloadIndex(0),
      receivedCrc(0)
{
}

void ArduinoProtocol::begin(long baudRate)
{
    serial.begin(baudRate);
    resetParser();
}

void ArduinoProtocol::update()
{
    while (serial.available()) {
        uint8_t value = serial.read();
        processByte(value);
    }
}


// ============================================================
// ENVIO DOS TIPOS EXIGIDOS
// ============================================================

bool ArduinoProtocol::sendByte(uint8_t value)
{
    return sendFrame(
        TYPE_BYTE,
        &value,
        sizeof(value)
    );
}

bool ArduinoProtocol::sendWord(uint16_t value)
{
    uint8_t payload[2];

    // Little endian
    payload[0] = value & 0xFF;
    payload[1] = (value >> 8) & 0xFF;

    return sendFrame(
        TYPE_WORD,
        payload,
        2
    );
}

bool ArduinoProtocol::sendFloat(float value)
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

bool ArduinoProtocol::sendData(
    const uint8_t *data,
    uint16_t size
)
{
    if (data == nullptr || size == 0) {
        return false;
    }

    if (size > MAX_PAYLOAD) {
        return false;
    }

    return sendFrame(
        TYPE_DATA,
        data,
        size
    );
}


// ============================================================
// ENVIO DE QUADRO
// ============================================================

bool ArduinoProtocol::sendFrame(
    uint8_t type,
    const uint8_t *payload,
    uint16_t size
)
{
    if (size > MAX_PAYLOAD) {
        return false;
    }

    uint8_t currentSequence = sequence++;

    uint16_t crc = calculateCRC(
        type,
        currentSequence,
        size,
        payload
    );

    for (uint8_t attempt = 0; attempt < MAX_RETRIES; attempt++) {

        // SOF
        serial.write(SOF);

        // TYPE
        serial.write(type);

        // SEQUENCE
        serial.write(currentSequence);

        // SIZE - little endian
        serial.write(size & 0xFF);
        serial.write((size >> 8) & 0xFF);

        // PAYLOAD
        for (uint16_t i = 0; i < size; i++) {
            serial.write(payload[i]);
        }

        // CRC
        uint16_t frameCrc = crc;

        /*
         * Simulação de erro:
         * somente a primeira tentativa terá CRC inválido.
         * Assim, o receptor envia NACK e a segunda tentativa
         * será correta.
         */
        if (corruptNextFrame && attempt == 0) {
            frameCrc ^= 0xFFFF;
            corruptNextFrame = false;
        }

        serial.write(frameCrc & 0xFF);
        serial.write((frameCrc >> 8) & 0xFF);

        serial.flush();

        // Aguarda ACK/NACK
        if (waitForResponse(currentSequence)) {
            return true;
        }
    }

    return false;
}


// ============================================================
// ESPERA PELO ACK/NACK
// ============================================================

bool ArduinoProtocol::waitForResponse(
    uint8_t expectedSequence
)
{
    responseReceived = false;
    responseAccepted = false;
    responseSequence = 0;

    unsigned long startTime = millis();

    while (millis() - startTime < TIMEOUT_MS) {

        while (serial.available()) {

            uint8_t value = serial.read();

            processByte(value);

            if (
                responseReceived &&
                responseSequence == expectedSequence
            ) {
                return responseAccepted;
            }
        }
    }

    return false;
}


// ============================================================
// PARSER
// ============================================================

void ArduinoProtocol::processByte(uint8_t value)
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

            receivedPayload[receivedPayloadIndex++] = value;

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
// PROCESSAMENTO DO QUADRO
// ============================================================

void ArduinoProtocol::processFrame()
{
    uint16_t calculatedCRC = calculateCRC(
        receivedType,
        receivedSequence,
        receivedSize,
        receivedPayload
    );

    // --------------------------------------------------------
    // CRC inválido
    // --------------------------------------------------------

    if (calculatedCRC != receivedCrc) {

        sendNack(receivedSequence);

        return;
    }


    // --------------------------------------------------------
    // ACK / NACK
    // --------------------------------------------------------

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


    // --------------------------------------------------------
    // Verificação de duplicação
    // --------------------------------------------------------

    if (
        hasReceivedSequence &&
        receivedSequence == lastReceivedSequence
    ) {
        /*
         * A mensagem já foi processada.
         *
         * Isso normalmente acontece quando:
         * 1. recebemos uma mensagem;
         * 2. enviamos ACK;
         * 3. o ACK se perdeu;
         * 4. o transmissor envia novamente.
         *
         * Não processamos os dados novamente.
         * Apenas reenviamos o ACK.
         */

        sendAck(receivedSequence);

        return;
    }


    // --------------------------------------------------------
    // Verificação do tamanho dos tipos conhecidos
    // --------------------------------------------------------

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


    // --------------------------------------------------------
    // Processamento
    // --------------------------------------------------------

    switch (receivedType) {

        case TYPE_BYTE:

            if (onByte != nullptr) {
                onByte(receivedPayload[0]);
            }

            break;


        case TYPE_WORD:
        {
            uint16_t value =
                (uint16_t)receivedPayload[0] |
                ((uint16_t)receivedPayload[1] << 8);

            if (onWord != nullptr) {
                onWord(value);
            }

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

            if (onFloat != nullptr) {
                onFloat(value);
            }

            break;
        }


        case TYPE_DATA:

            if (onData != nullptr) {
                onData(
                    receivedPayload,
                    receivedSize
                );
            }

            break;


        default:

            sendNack(receivedSequence);
            return;
    }


    // --------------------------------------------------------
    // Mensagem processada com sucesso
    // --------------------------------------------------------

    hasReceivedSequence = true;
    lastReceivedSequence = receivedSequence;

    sendAck(receivedSequence);
}


// ============================================================
// ACK
// ============================================================

void ArduinoProtocol::sendAck(uint8_t sequence)
{
    /*
     * Simulação de perda de ACK.
     *
     * Não enviamos nada nesta primeira tentativa.
     * O transmissor irá detectar timeout e retransmitir.
     */

    if (dropNextAck) {
        dropNextAck = false;
        return;
    }

    uint16_t crc = calculateCRC(
        TYPE_ACK,
        sequence,
        0,
        nullptr
    );

    serial.write(SOF);
    serial.write(TYPE_ACK);
    serial.write(sequence);

    serial.write(0);
    serial.write(0);

    serial.write(crc & 0xFF);
    serial.write((crc >> 8) & 0xFF);

    serial.flush();
}


// ============================================================
// NACK
// ============================================================

void ArduinoProtocol::sendNack(uint8_t sequence)
{
    uint16_t crc = calculateCRC(
        TYPE_NACK,
        sequence,
        0,
        nullptr
    );

    serial.write(SOF);
    serial.write(TYPE_NACK);
    serial.write(sequence);

    serial.write(0);
    serial.write(0);

    serial.write(crc & 0xFF);
    serial.write((crc >> 8) & 0xFF);

    serial.flush();
}


// ============================================================
// CRC-16-CCITT
// ============================================================

uint16_t ArduinoProtocol::calculateCRC(
    uint8_t type,
    uint8_t sequence,
    uint16_t size,
    const uint8_t *payload
)
{
    uint16_t crc = 0xFFFF;

    updateCRC(crc, type);
    updateCRC(crc, sequence);

    updateCRC(crc, size & 0xFF);
    updateCRC(crc, (size >> 8) & 0xFF);

    for (uint16_t i = 0; i < size; i++) {
        updateCRC(crc, payload[i]);
    }

    return crc;
}

void ArduinoProtocol::updateCRC(
    uint16_t &crc,
    uint8_t value
)
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


// ============================================================
// RESET DO PARSER
// ============================================================

void ArduinoProtocol::resetParser()
{
    parserState = WAIT_SOF;

    receivedType = 0;
    receivedSequence = 0;
    receivedSize = 0;
    receivedPayloadIndex = 0;
    receivedCrc = 0;
}


// ============================================================
// SIMULAÇÃO DE FALHAS
// ============================================================

void ArduinoProtocol::simulateNextCRCError()
{
    corruptNextFrame = true;
}

void ArduinoProtocol::simulateNextAckLoss()
{
    dropNextAck = true;
}