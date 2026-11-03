# Cofre Cromático — primeira versão

Implementação inicial para **ESP32 TTGO T-Display + sensor TCS34725**. A senha de outro puzzle está simulada no código; MQTT ainda não foi integrado.

## O que esta versão faz

1. Inicializa o display e o sensor de cor.
2. Permite cadastrar quatro cartões, apresentados individualmente ao sensor.
3. Converte a senha numérica mock em um índice de `0` a `23`, usando `senha % 24`.
4. Mapeia esse índice para uma das 24 permutações dos cartões `1, 2, 3, 4`.
5. Permite apresentar novamente os quatro cartões na ordem escolhida.
6. Identifica cada cartão pela distância entre as cores RGB normalizadas e valida a sequência.

A sequência esperada é impressa no Monitor Serial para facilitar os testes. Ela não é exibida no display.

## Estrutura

```text
cofre-cromatico/
├── src/
│   └── cofre-cromatico.ino
└── README.md
```

## Hardware necessário

| Componente | Quantidade | Uso |
|---|---:|---|
| ESP32 TTGO T-Display 1.14" | 1 | Controlador, Wi-Fi e display |
| Sensor de cor TCS34725 (breakout) | 1 | Identificar os cartões |
| Cartões foscos de cores distintas | 4 | Amostras físicas |
| Protoboard | 1 | Montagem |
| Jumpers fêmea-fêmea / macho-fêmea | Conforme necessário | Ligações |
| Resistor de 10 kΩ | 1, se necessário | Pull-up externo do GPIO35, caso a placa não tenha pull-up no botão |
| Fonte/cabo USB | 1 | Alimentação e programação |

Use cartões foscos e mantenha distância, orientação e iluminação constantes. Evite luz ambiente variável e reflexos.

## Ligações

### TCS34725 → TTGO T-Display

| TCS34725 | TTGO T-Display | Observação |
|---|---|---|
| VIN / VCC | 3V3 | Confirme a tensão aceita pelo breakout específico. 3,3 V é a opção conservadora. |
| GND | GND | Terra comum obrigatório. |
| SDA | GPIO 21 | I²C SDA escolhido no código. |
| SCL | GPIO 22 | I²C SCL escolhido no código. |
| LED | Sem ligação / conforme breakout | Alguns módulos possuem pino de controle do LED; não é necessário nesta versão. |

**Atenção:** GPIO 21 e 22 foram escolhidos como pinos I²C no código, mas confirme o pinout e a disponibilidade na revisão exata da sua TTGO T-Display. Eles não são os pinos do display TFT configurado pela biblioteca.

### Botões

Esta versão utiliza os dois botões já presentes na TTGO T-Display:

| Botão | GPIO no código | Função |
|---|---:|---|
| Botão A / botão de boot | GPIO 0 | Captura/cadastra o cartão atual |
| Botão B | GPIO 35 | Confirma a sequência após ler os quatro cartões |

O GPIO 35 é somente entrada e não possui pull-up interno. Algumas revisões da T-Display já possuem o circuito do botão na placa. **Verifique o esquema da sua revisão.** Se o botão B não fornecer nível lógico estável, use um resistor externo de 10 kΩ entre GPIO35 e 3V3, mantendo o botão entre GPIO35 e GND.

Não mantenha o botão A pressionado durante a energização/reset, pois GPIO0 participa do modo de boot do ESP32.

## Bibliotecas

Instale pelo Library Manager da Arduino IDE:

- **Adafruit TCS34725**
- **Adafruit BusIO** (dependência da biblioteca Adafruit)
- **TFT_eSPI**

A biblioteca `TFT_eSPI` exige configuração para a TTGO T-Display. Configure o setup correspondente à sua revisão de placa no arquivo `User_Setup_Select.h` da biblioteca, ou use o setup disponibilizado pelo fabricante. Não selecione um setup TFT aleatório: os pinos do display variam conforme a placa/revisão.

## Configuração da senha mock

No início do arquivo `.ino`:

```cpp
const char MOCK_PASSWORD[] = "58321";
```

A senha é processada dígito a dígito para calcular o resto da divisão por 24, sem risco de overflow de um `int` para senhas longas.

O índice seleciona uma permutação em ordem lexicográfica:

- índice 0 → `1, 2, 3, 4`
- índice 1 → `1, 2, 4, 3`
- ...
- índice 23 → `4, 3, 2, 1`

Os IDs 1 a 4 correspondem à ordem em que os cartões foram cadastrados, não ao nome/cor impressa neles.

## Operação

1. Ligue a placa e abra o Monitor Serial em **115200 baud**.
2. Aguarde a tela de cadastro.
3. Aproxime o primeiro cartão e pressione A. Repita para os quatro cartões, sempre na mesma posição e iluminação.
4. Após cadastrar quatro cartões, a placa passa para a entrada da sequência.
5. Apresente os quatro cartões na ordem que deseja testar, pressionando A após cada leitura.
6. Pressione B para validar.
7. Se errar, pressione A para limpar a entrada e tentar novamente.

O Monitor Serial mostra a senha mock, o índice calculado, a sequência esperada e as leituras classificadas. Não use essa saída durante a demonstração se ela revelar a solução aos jogadores.

## Parâmetros que provavelmente precisarão de ajuste

No `.ino`:

- `MIN_CLEAR_VALUE`: luminosidade mínima para aceitar uma leitura.
- `MAX_COLOR_DISTANCE`: distância máxima para reconhecer um cartão cadastrado.
- `MIN_CARD_SEPARATION`: distância mínima entre dois cartões no cadastro.
- `SAMPLES_PER_READING`: quantidade de leituras usadas para calcular a média.

Comecem testando os quatro cartões com iluminação controlada. Se cartões forem confundidos, ajustem primeiro a montagem física, distância e iluminação; só depois alterem as tolerâncias.

## Limitações conhecidas desta versão

- Não há MQTT ainda: `MOCK_PASSWORD` simula a senha recebida.
- Não há limite de tentativas nem temporizador.
- A identificação depende de calibração física e pode falhar com iluminação variável.
- A sequência é calculada a partir dos IDs atribuídos na etapa de cadastro. Portanto, a ordem de cadastro precisa ser mantida como referência durante a rodada.
- O pinout do display TFT deve ser configurado na biblioteca `TFT_eSPI` conforme a revisão da placa.

## Próximas integrações

Quando o protocolo do outro grupo estiver definido, substituir a origem de `MOCK_PASSWORD` por uma variável preenchida pelo callback MQTT. A função `passwordToPermutationIndex()` e a lógica de validação podem permanecer independentes da camada de comunicação.
