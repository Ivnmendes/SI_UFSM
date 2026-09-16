# Trabalho 1 — Protocolo de Comunicação Serial entre Arduinos

## 1. Introdução

Este trabalho apresenta a implementação de um protocolo próprio de
comunicação serial entre dois microcontroladores Arduino Uno.

O objetivo é estabelecer uma comunicação confiável entre os dois
dispositivos, permitindo o envio de diferentes tipos de dados: `byte`,
`word`, `float` e dados de tamanho variável.

Além do envio dos dados, o protocolo possui mecanismos para detectar
erros de transmissão, confirmar o recebimento das mensagens e realizar
retransmissões quando necessário.

A comunicação utiliza a biblioteca `SoftwareSerial`, com os pinos
digitais 10 e 11, enquanto a porta serial física do Arduino (D0/D1) é
utilizada para interação com o usuário e depuração.

## 2. Objetivos

- Implementar um protocolo de comunicação serial próprio.
- Permitir a identificação do tipo de dado recebido.
- Transmitir dados de tamanho fixo e variável.
- Detectar erros através de CRC16.
- Utilizar mensagens de confirmação (`ACK`) e rejeição (`NACK`).
- Implementar timeout para detectar ausência de resposta.
- Realizar retransmissão em caso de falha.
- Detectar mensagens duplicadas causadas por retransmissões.
- Informar ao usuário se a transmissão foi concluída com sucesso ou
  falhou.

## 3. Arquitetura da comunicação

Foram utilizados dois Arduino Uno:

- **Arduino A:** transmissor.
- **Arduino B:** receptor.

A comunicação entre os dispositivos utiliza `SoftwareSerial` configurada
em **9600 baud**.

### 3.1 Ligações

``` text
Arduino A                         Arduino B

D11 (TX)  ---------------------> D10 (RX)
D10 (RX)  <--------------------- D11 (TX)
GND       ---------------------- GND
```

A porta serial física é utilizada pelos terminais:

``` text
Arduino A D0/D1 <----> Terminal A
Arduino B D0/D1 <----> Terminal B
```

## 4. Estrutura do protocolo

Cada mensagem possui o seguinte frame:

``` text
+------+-------+------+-------+---------+-------+
| SOF  | TYPE  | SEQ  | SIZE  | PAYLOAD | CRC16 |
+------+-------+------+-------+---------+-------+
| 1 B  | 1 B   | 1 B  | 2 B   | N bytes | 2 B  |
+------+-------+------+-------+---------+-------+
```

### 4.1 SOF

`SOF` (Start of Frame) possui o valor `0xAA` e indica o início de uma
mensagem.

### 4.2 TYPE

O campo `TYPE` identifica o tipo da mensagem.

| Valor  | Tipo  | Descrição                 |
|--------|-------|---------------------------|
| `0x01` | BYTE  | Valor de 8 bits           |
| `0x02` | WORD  | Valor de 16 bits          |
| `0x03` | FLOAT | Valor de ponto flutuante  |
| `0x04` | DATA  | Dados de tamanho variável |
| `0x10` | ACK   | Confirmação               |
| `0x11` | NACK  | Rejeição                  |

### 4.3 SEQ

`SEQ` é o número sequencial da mensagem. Possui 1 byte, variando de 0 a
255 e retornando a 0 após 255.

Ele permite associar uma resposta à mensagem transmitida e detectar
retransmissões.

### 4.4 SIZE

`SIZE` informa o tamanho do `PAYLOAD`. Possui 2 bytes e é transmitido em
formato little-endian.

Embora o campo permita até 65535 bytes, a implementação utiliza um
limite prático de **128 bytes**, devido à memória do Arduino Uno.

### 4.5 PAYLOAD

Contém os dados da mensagem. Seu conteúdo depende do campo `TYPE`.

Para `FLOAT`, os 4 bytes da representação binária do valor são
transmitidos diretamente.

Para `DATA`, podem ser transmitidas sequências de bytes de tamanho
variável.

### 4.6 CRC16

O protocolo utiliza **CRC-16-CCITT** para verificar a integridade da
mensagem.

O cálculo é realizado sobre:

``` text
TYPE + SEQ + SIZE + PAYLOAD
```

O `SOF` não participa do cálculo.

O receptor recalcula o CRC e compara o resultado com o valor recebido.

## 5. ACK e NACK

### ACK

O `ACK` confirma que a mensagem foi recebida corretamente. Ele contém o
número de sequência da mensagem confirmada.

### NACK

O `NACK` informa que a mensagem não foi aceita, principalmente quando o
CRC calculado pelo receptor é diferente do CRC recebido.

Ao receber um `NACK`, o transmissor realiza uma nova tentativa.

## 6. Funcionamento da transmissão

O processo é:

1.  O transmissor monta o frame.
2.  Define o número de sequência.
3.  Calcula o CRC16.
4.  Envia o frame.
5.  Aguarda `ACK` ou `NACK`.
6.  O receptor recebe o frame.
7.  O receptor verifica o CRC.
8.  Se estiver correto, processa a mensagem e envia `ACK`.
9.  Se estiver incorreto, envia `NACK`.
10. O transmissor encerra com sucesso após `ACK`.
11. Em caso de `NACK` ou timeout, ocorre retransmissão.

## 7. Timeout e retransmissão

Foi definido:

``` text
Timeout: 500 ms
Máximo de tentativas: 3
```

Em caso de ausência de resposta:

``` text
Envio
  ↓
500 ms
  ↓
TIMEOUT
  ↓
Retransmissão
```

Após três tentativas sem confirmação válida, a função de envio retorna
`false` e o usuário é informado sobre a falha.

## 8. Detecção de mensagens duplicadas

A perda de um `ACK` pode fazer o transmissor reenviar uma mensagem que o
receptor já processou.

O receptor utiliza o `SEQ` para identificar essa situação.

Quando recebe novamente uma mensagem já processada:

- não processa o payload novamente;
- identifica a mensagem como duplicada;
- envia novamente o `ACK`.

Isso evita que uma retransmissão provoque o processamento duplicado da
mesma operação.

## 9. Máquina de estados do receptor

O receptor monta os frames byte a byte através dos seguintes estados:

``` text
WAIT_SOF
   ↓
READ_TYPE
   ↓
READ_SEQUENCE
   ↓
READ_SIZE_LOW
   ↓
READ_SIZE_HIGH
   ↓
READ_PAYLOAD
   ↓
READ_CRC_LOW
   ↓
READ_CRC_HIGH
   ↓
PROCESS_FRAME
```

- `WAIT_SOF`: aguarda `0xAA`.
- `READ_TYPE`: recebe o tipo.
- `READ_SEQUENCE`: recebe o número de sequência.
- `READ_SIZE_LOW/HIGH`: recebe o tamanho.
- `READ_PAYLOAD`: recebe os dados.
- `READ_CRC_LOW/HIGH`: recebe o CRC.
- `PROCESS_FRAME`: verifica e processa o frame.

## 10. Funções de envio

O protocolo implementa as funções exigidas:

``` cpp
bool sendByte(uint8_t value);
bool sendWord(uint16_t value);
bool sendFloat(float value);
bool sendData(const uint8_t *data, uint16_t size);
```

### `sendByte`

Transmite um valor de 8 bits. No teste foi utilizado:

``` text
42
```

### `sendWord`

Transmite um valor de 16 bits. No teste foi utilizado:

``` text
1500
```

### `sendFloat`

Transmite um número de ponto flutuante. No teste foi utilizado:

``` text
3.14159
```

### `sendData`

Transmite uma sequência de bytes com tamanho variável. No teste foi
utilizada a mensagem:

``` text
Ola! Esta e uma DATA de tamanho variavel.
```

## 11. Testes realizados

### 11.1 BYTE

Comando:

``` text
1
```

O Arduino A transmite `BYTE = 42`.

O Arduino B identifica o tipo e apresenta o valor recebido. A
transmissão é confirmada por `ACK`.

### 11.2 WORD

Comando:

``` text
2
```

O Arduino A transmite `WORD = 1500`.

O Arduino B identifica o tipo e apresenta o valor recebido.

### 11.3 FLOAT

Comando:

``` text
3
```

O Arduino A transmite `FLOAT = 3.14159`.

O Arduino B interpreta o payload como `FLOAT` e recupera o valor.

### 11.4 DATA variável

Comando:

``` text
4
```

O Arduino A transmite:

``` text
Ola! Esta e uma DATA de tamanho variavel.
```

O Arduino B utiliza o campo `SIZE` para determinar o tamanho do payload.

## 12. Teste de erro de CRC

O comando `5` no Arduino A realiza um teste no qual o próximo frame tem
seu CRC alterado propositalmente.

O fluxo esperado é:

``` text
Arduino A
   ↓
Frame com CRC inválido
   ↓
Arduino B
   ↓
CRC inválido → NACK
   ↓
Arduino A
   ↓
Retransmissão
   ↓
Arduino B
   ↓
Frame correto → ACK
```

Esse teste demonstra a detecção de erro e a retransmissão.

## 13. Teste de perda de ACK

No Arduino B, o comando `5` configura a perda proposital do próximo
`ACK`.

Em seguida, o comando `1` é executado no Arduino A.

O Arduino B apresentou:

``` text
Proximo ACK sera perdido.
BYTE recebido: 42
[TESTE] ACK perdido propositalmente.
Mensagem duplicada detectada.
```

Esse resultado demonstra que:

1.  o pacote foi recebido;
2.  o BYTE foi processado;
3.  o ACK foi perdido propositalmente;
4.  o transmissor realizou uma nova tentativa;
5.  o receptor identificou a retransmissão como duplicada;
6.  o pacote não foi processado novamente;
7.  o ACK foi reenviado.

## 14. Resultados

| Teste                          | Resultado |
|--------------------------------|-----------|
| BYTE                           | Funcionou |
| WORD                           | Funcionou |
| FLOAT                          | Funcionou |
| DATA variável                  | Funcionou |
| Detecção de erro por CRC       | Funcionou |
| NACK                           | Funcionou |
| Retransmissão                  | Funcionou |
| Timeout                        | Funcionou |
| Perda proposital de ACK        | Funcionou |
| Detecção de mensagem duplicada | Funcionou |
| ACK                            | Funcionou |

## 15. Decisões de projeto

### SoftwareSerial

`SoftwareSerial` foi utilizada para separar a comunicação do protocolo
da interface serial usada para interação e depuração.

### CRC16

O CRC16 foi escolhido para detectar alterações no frame durante a
transmissão.

### ACK/NACK

ACK e NACK permitem que o transmissor saiba se a mensagem foi aceita ou
se deve ser retransmitida.

### Número de sequência

O `SEQ` permite identificar cada transmissão e detectar mensagens
duplicadas.

### Limite de payload

Foi adotado limite prático de 128 bytes para evitar uso excessivo da
memória do Arduino Uno.

## 16. Limitações

- O protocolo foi desenvolvido para uma comunicação simples entre dois
  Arduino Uno.
- O payload possui limite prático de 128 bytes.
- O `FLOAT` é transmitido diretamente em sua representação binária,
  sendo adequado aos dispositivos utilizados, mas não sendo um formato
  universal entre arquiteturas diferentes.
- O número de sequência possui apenas 1 byte e é reutilizado após 256
  mensagens.
- A implementação não foi projetada para múltiplos transmissores
  simultâneos.

## 17. Ambiente utilizado

### Hardware

- 2 × Arduino Uno

### Comunicação

- `SoftwareSerial`
- 9600 baud
- D10/D11 para comunicação entre os Arduinos

### Simulação

- SimulIDE 2.0.0

### Ferramentas

- Arduino IDE
- Arduino CLI
- Compilação para `arduino:avr:uno`

## 18. Conclusão

Foi desenvolvido um protocolo próprio de comunicação serial entre dois
Arduino Uno capaz de transmitir `BYTE`, `WORD`, `FLOAT` e dados de
tamanho variável.

A estrutura de frame utiliza identificação de tipo, número de sequência,
tamanho do payload e CRC16. Para aumentar a confiabilidade, foram
implementados `ACK`, `NACK`, timeout, retransmissão e detecção de
mensagens duplicadas.

Os testes realizados demonstraram o funcionamento desses mecanismos,
incluindo a simulação de erro de CRC e a perda proposital de um ACK.

A implementação, portanto, atende aos requisitos propostos e demonstra,
na prática, mecanismos de detecção e recuperação de falhas em uma
comunicação serial.
