#ifndef ARDUINO_PROTOCOL_H
#define ARDUINO_PROTOCOL_H

#include <Arduino.h>
#include <SoftwareSerial.h>

class ArduinoProtocol {
public:

    // Marcador de início de quadro
    static const uint8_t SOF = 0xAA;

    // Tipos de mensagem
    static const uint8_t TYPE_BYTE  = 0x01;
    static const uint8_t TYPE_WORD  = 0x02;
    static const uint8_t TYPE_FLOAT = 0x03;
    static const uint8_t TYPE_DATA  = 0x04;

    // Controle
    static const uint8_t TYPE_ACK  = 0x10;
    static const uint8_t TYPE_NACK = 0x11;

    // Configurações
    static const uint16_t MAX_PAYLOAD = 128;
    static const unsigned long TIMEOUT_MS = 500;
    static const uint8_t MAX_RETRIES = 3;

    typedef void (*ByteCallback)(uint8_t value);
    typedef void (*WordCallback)(uint16_t value);
    typedef void (*FloatCallback)(float value);
    typedef void (*DataCallback)(const uint8_t *data, uint16_t size);

    ArduinoProtocol(
        SoftwareSerial &serial,
        ByteCallback byteCallback = nullptr,
        WordCallback wordCallback = nullptr,
        FloatCallback floatCallback = nullptr,
        DataCallback dataCallback = nullptr
    );

    void begin(long baudRate);
    void update();

    bool sendByte(uint8_t value);
    bool sendWord(uint16_t value);
    bool sendFloat(float value);
    bool sendData(const uint8_t *data, uint16_t size);

    // Funções utilizadas para demonstrar falhas
    void simulateNextCRCError();
    void simulateNextAckLoss();

private:

    SoftwareSerial &serial;

    ByteCallback onByte;
    WordCallback onWord;
    FloatCallback onFloat;
    DataCallback onData;

    uint8_t sequence;

    // Controle de mensagens recebidas
    bool hasReceivedSequence;
    uint8_t lastReceivedSequence;

    // Controle de ACK/NACK
    bool responseReceived;
    bool responseAccepted;
    uint8_t responseSequence;

    // Simulação de falhas
    bool corruptNextFrame;
    bool dropNextAck;

    // Estado do parser
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

    ParserState parserState;

    uint8_t receivedType;
    uint8_t receivedSequence;
    uint16_t receivedSize;
    uint16_t receivedPayloadIndex;
    uint8_t receivedPayload[MAX_PAYLOAD];

    uint16_t receivedCrc;

    void processByte(uint8_t value);
    void processFrame();

    bool sendFrame(
        uint8_t type,
        const uint8_t *payload,
        uint16_t size
    );

    bool waitForResponse(uint8_t expectedSequence);

    void sendAck(uint8_t sequence);
    void sendNack(uint8_t sequence);

    uint16_t calculateCRC(
        uint8_t type,
        uint8_t sequence,
        uint16_t size,
        const uint8_t *payload
    );

    void updateCRC(uint16_t &crc, uint8_t value);

    void resetParser();
};

#endif