#include <SoftwareSerial.h>
#include "ArduinoProtocol.h"

// D10 = RX
// D11 = TX
SoftwareSerial serialLink(10, 11);


// ------------------------------------------------------------
// CALLBACKS
// ------------------------------------------------------------

void receivedByte(uint8_t value);
void receivedWord(uint16_t value);
void receivedFloat(float value);
void receivedData(const uint8_t *data, uint16_t size);


ArduinoProtocol protocol(
    serialLink,
    receivedByte,
    receivedWord,
    receivedFloat,
    receivedData
);


// ------------------------------------------------------------
// SETUP
// ------------------------------------------------------------

void setup()
{
    Serial.begin(9600);

    protocol.begin(9600);

    Serial.println("Arduino A iniciado.");
    Serial.println();
    Serial.println("Comandos:");
    Serial.println("1 - Enviar BYTE");
    Serial.println("2 - Enviar WORD");
    Serial.println("3 - Enviar FLOAT");
    Serial.println("4 - Enviar DATA");
    Serial.println("5 - Testar erro de CRC");
    Serial.println();
}


// ------------------------------------------------------------
// LOOP
// ------------------------------------------------------------

void loop()
{
    protocol.update();

    if (Serial.available()) {

        char command = Serial.read();

        switch (command) {

            case '1':
            {
                uint8_t value = 42;

                Serial.println("Enviando BYTE...");

                if (protocol.sendByte(value)) {
                    Serial.println("BYTE enviado com sucesso.");
                }
                else {
                    Serial.println("Falha ao enviar BYTE.");
                }

                break;
            }


            case '2':
            {
                uint16_t value = 1500;

                Serial.println("Enviando WORD...");

                if (protocol.sendWord(value)) {
                    Serial.println("WORD enviado com sucesso.");
                }
                else {
                    Serial.println("Falha ao enviar WORD.");
                }

                break;
            }


            case '3':
            {
                float value = 3.14159;

                Serial.println("Enviando FLOAT...");

                if (protocol.sendFloat(value)) {
                    Serial.println("FLOAT enviado com sucesso.");
                }
                else {
                    Serial.println("Falha ao enviar FLOAT.");
                }

                break;
            }


            case '4':
            {
                const char message[] =
                    "Ola! Esta e uma mensagem variavel.";

                Serial.println("Enviando DATA...");

                if (
                    protocol.sendData(
                        (const uint8_t *)message,
                        strlen(message) + 1
                    )
                ) {
                    Serial.println("DATA enviada com sucesso.");
                }
                else {
                    Serial.println("Falha ao enviar DATA.");
                }

                break;
            }


            case '5':
            {
                Serial.println(
                    "Proximo quadro sera enviado com CRC incorreto."
                );

                protocol.simulateNextCRCError();

                uint8_t value = 99;

                if (protocol.sendByte(value)) {
                    Serial.println(
                        "Mensagem recuperada apos erro."
                    );
                }
                else {
                    Serial.println(
                        "Falha mesmo apos retransmissoes."
                    );
                }

                break;
            }
        }
    }
}


// ------------------------------------------------------------
// CALLBACKS
// ------------------------------------------------------------

void receivedByte(uint8_t value)
{
    Serial.print("BYTE recebido: ");
    Serial.println(value);
}

void receivedWord(uint16_t value)
{
    Serial.print("WORD recebido: ");
    Serial.println(value);
}

void receivedFloat(float value)
{
    Serial.print("FLOAT recebido: ");
    Serial.println(value, 5);
}

void receivedData(
    const uint8_t *data,
    uint16_t size
)
{
    Serial.print("DATA recebida: ");

    for (uint16_t i = 0; i < size; i++) {
        Serial.write(data[i]);
    }

    Serial.println();
}