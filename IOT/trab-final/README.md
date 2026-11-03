# Plano de implementação — Cofre Cromático (ESP32 + TCS34725 + MQTT)

Projeto proposto para o Grupo 7 — Bruno e Ivan

## 1. Visão geral do projeto

O objetivo é desenvolver um módulo de puzzle no qual o jogador precisa identificar e ordenar amostras coloridas utilizando o sensor TCS34725 para desbloquear um cofre fictício.

O sensor será o principal componente de interação: o jogador deverá apresentar cartões coloridos diante dele, realizar leituras e reproduzir uma sequência de cores que obedeça a uma regra apresentada pelo sistema.

Uma pista complementar será recebida de outro módulo por MQTT, fazendo com que o desafio dependa parcialmente dos demais grupos.

Conceito central: analisar cores, interpretar uma regra, descobrir a ordem correta e inserir a combinação no cofre.

### Características principais

- Leitura de cores utilizando o TCS34725.
- Interface visual pelo display da TTGO T-Display.
- Interação física por meio de cartões coloridos e botões.
- Geração de desafios com regras variáveis.
- Comunicação MQTT para receber pistas e publicar resultados.
- Controle de tentativas, erros e conclusão.
- Funcionamento independente (standalone) quando não houver central.

## 2. Componentes e materiais

[Плата розробника ESP32 T-Display (16MB) з дисплеєм 1.14 дюйма та USB-UART CH9102F, ціна 370 ₴: купити на Prom.ua | Україна, Дніпро](https://images.openai.com/static-rsc-4/F--95Ts1Rz6p5fJYR0nvMb1X5VLD517p_exGDOealzCopJFr28l7q3Bbg4eHwKxbqynGAroCv9aYxfNlWAlGmb43S4jEE4Z32Imr8O3sHz04HGpDazDhyFdq4RwUv2Hg0RpiAeI3sRGFNsZl6Q6CDSwnsNFsFjXZ3l-4iiodJps?purpose=inline)

ESP32 TTGO T-Display

Processamento, display, Wi-Fi, MQTT e controle do desafio.

Obrigatório

[RGB Color Sensor with IR filter and White LED - TCS34725 : Adafruit Industries, Unique & fun DIY electronics and kits](https://images.openai.com/static-rsc-4/AuyKIfAlBf1cKEotoHMMOTPuIGWOLa8UaPyIfUs4Z1HGkfcpAFadT6aWuGmpCCKR7Mpfc_YVBeQMhM0Tg0MAzXJ8YxIc_XIPWOPESh2ek2SOjFD9QNhmD2DFnDe86m3Ag9mMduMV3pAv0L-ux9qcNUniyzhu81GMxaGidp-t60w?purpose=inline)

Sensor TCS34725

Leitura dos canais RGB e luminosidade das amostras.

Obrigatório

[Low Temperature Environmental Polyester Primid Powder Coatings - Polyester Haa Powder Coating and Pure Polyester Powder Coating](https://images.openai.com/static-rsc-4/crl479ZSFZeYlNukc3077TzUNIX54BdcHxGf-xhoL4P8UDApLTsoccWcE4xHsThl_jeyZLSGVTWdPM0sqPwqT6cn88gU1oGkLc6sTDmW3p2IJVbci8P_Vmd6KXXw4l5WhK7-BFGbyUMT_WIn1SyiggOSegsrvkomQN-G2OHoHH4?purpose=inline)

Quatro cartões coloridos

Amostras que serão apresentadas ao sensor. Sugestão: vermelho, verde, azul e amarelo.

Obrigatório

[Tact Switch 6x6mm / 5mm THT - 2pin - 5szt. Sklep Botland](https://images.openai.com/static-rsc-4/vgsqoLjNzFbhyTV_b9zc-fh_JMC40b_BjyPy75wnUwiCd_6sHZE21hnO3RUvVMLES1vJHglPnYKcpjb60OhDOA6tLtyEpTSIG0vkEHed8xc25KTfRv-8qilnoPUUK8zOr8y8d_nEfK8g6AeAmFyL5EY3uJnxUpYpJMzJOtqd-Uk?purpose=inline)

Botões físicos

Confirmar leitura, iniciar desafio e validar combinação.

[100 Pack Bi-Color Red / Green Diffused LED, 3-Pin, 5mm Wide x 9mm Tall, T-1 3/4, HLMP-4000 - Walmart.com](https://images.openai.com/static-rsc-4/kTuvLSjwct-_90sWE3d-VqZ6xnl7KZjJ1OAg4p4GiSood3dkXwKEQRWpdtxBwd4JgOcDPf2hpYU5pGyrBVARAFdIg26d8liElDyrwXXV8qWy8WwewFnQL3quzXcjiFmxRBT7djYYVybglI0M24ISWzCwsam5Ta7_nmYq75G0sVo?purpose=inline)

LEDs (opcionais)

Indicação de leitura válida, erro e sucesso.

Também serão necessários:

- Protoboard e jumpers.
- Resistores adequados aos LEDs e botões, se necessário.
- Estrutura física para posicionar o sensor.
- Cartolina, papel ou plástico fosco para as amostras.
- Cabo USB para programação e alimentação.

## 3. Mecânica do jogo

A partida será dividida em cinco etapas.

### Etapa 1 — Inicialização

O módulo inicializa o sensor, conecta-se à rede Wi-Fi e tenta estabelecer comunicação MQTT.

O display apresenta:

```
COFRE CROMATICO
----------------
SENSOR: OK
MQTT: CONECTANDO
AGUARDANDO...
```

Se não encontrar a central, entra em modo standalone e utiliza uma regra padrão.

### Etapa 2 — Escaneamento das amostras

O jogador apresenta os quatro cartões individualmente diante do TCS34725.

Para cada leitura, o sistema:

1. Captura os valores R, G, B e Clear.
2. Verifica se a iluminação é suficiente.
3. Calcula as proporções normalizadas.
4. Registra a leitura.
5. Apresenta o resultado no display.

Exemplo:

```
AMOSTRA 01
COR: VERMELHO

R: 0.62
G: 0.19
B: 0.19

LEITURA SALVA!
```

Os valores acima são ilustrativos.

### Etapa 3 — Recebimento da pista

Após o escaneamento, o módulo recebe uma regra de outro grupo.

Exemplo:

```
REGRA RECEBIDA:

ORDENE AS CORES
PELO AZUL CRESCENTE
```

Outras regras possíveis:

- Vermelho crescente.
- Verde decrescente.
- Azul crescente.
- Luminosidade crescente.

A regra determina qual característica deve ser usada para ordenar as amostras.

### Etapa 4 — Inserção da combinação

O jogador apresenta novamente os quatro cartões, agora na ordem que acredita ser correta.

O ESP32 reconhece cada amostra, associa-a à identidade registrada durante o escaneamento inicial e armazena a sequência.

O display apresenta:

```
COMBINACAO:
01 > 03 > 02 > 04

PRESSIONE CONFIRMAR
```

### Etapa 5 — Validação

O sistema compara a sequência apresentada com a sequência correta calculada a partir das medições iniciais e da regra recebida.

Combinação correta

- Exibe mensagem de sucesso.
- Acende LED verde, se instalado.
- Publica resultado positivo via MQTT.
- Aguarda o encerramento ou a próxima etapa da missão.

  Combinação incorreta
- Exibe mensagem de erro.
- Acende LED vermelho, se instalado.
- Publica resultado negativo via MQTT.
- Consome uma tentativa ou aplica penalidade de tempo.

## 4. Arquitetura do software

Recomendo separar o código em módulos independentes, em vez de implementar tudo dentro do `loop()` principal.

### Organização sugerida dos arquivos

```
cofre-cromatico/
│
├── cofre-cromatico.ino
│
├── config.h
├── sensor.h
├── sensor.cpp
├── display.h
├── display.cpp
├── puzzle.h
├── puzzle.cpp
├── mqtt_manager.h
├── mqtt_manager.cpp
├── buttons.h
└── buttons.cpp
```

Responsabilidade de cada arquivo:

| Arquivo               | Responsabilidade                       |
| --------------------- | -------------------------------------- |
| `cofre-cromatico.ino` | Inicialização e execução principal     |
| `config.h`            | Pinos, configurações e constantes      |
| `sensor.cpp`          | Leitura e classificação das cores      |
| `display.cpp`         | Telas e mensagens                      |
| `puzzle.cpp`          | Regras, combinação e validação         |
| `mqtt_manager.cpp`    | Conexão, publicação e recebimento MQTT |
| `buttons.cpp`         | Leitura dos botões e debounce          |

Essa organização facilita o trabalho dos dois integrantes: um pode desenvolver o sensor e a classificação enquanto o outro desenvolve o puzzle, display e comunicação. Depois vocês integram os componentes.

### Máquina de estados

O jogo deve possuir estados bem definidos:

\#chatgpt-mermaid-\_r_100\_{font-family:-apple-system-body,ui-sans-serif,-apple-system,system-ui,"Segoe UI",Helvetica,"Apple Color Emoji",Arial,sans-serif,"Segoe UI Emoji","Segoe UI Symbol";font-size:16px;fill:rgb(237, 237, 237);}@keyframes edge-animation-frame{from{stroke-dashoffset:0;}}@keyframes dash{to{stroke-dashoffset:0;}}#chatgpt-mermaid-\_r_100\_ .edge-animation-slow{stroke-dasharray:9,5!important;stroke-dashoffset:900;animation:dash 50s linear infinite;stroke-linecap:round;}#chatgpt-mermaid-\_r_100\_ .edge-animation-fast{stroke-dasharray:9,5!important;stroke-dashoffset:900;animation:dash 20s linear infinite;stroke-linecap:round;}#chatgpt-mermaid-\_r_100\_ .error-icon{fill:rgb(48, 48, 48);}#chatgpt-mermaid-\_r_100\_ .error-text{fill:rgb(237, 237, 237);stroke:rgb(237, 237, 237);}#chatgpt-mermaid-\_r_100\_ .edge-thickness-normal{stroke-width:1px;}#chatgpt-mermaid-\_r_100\_ .edge-thickness-thick{stroke-width:3.5px;}#chatgpt-mermaid-\_r_100\_ .edge-pattern-solid{stroke-dasharray:0;}#chatgpt-mermaid-\_r_100\_ .edge-thickness-invisible{stroke-width:0;fill:none;}#chatgpt-mermaid-\_r_100\_ .edge-pattern-dashed{stroke-dasharray:3;}#chatgpt-mermaid-\_r_100\_ .edge-pattern-dotted{stroke-dasharray:2;}#chatgpt-mermaid-\_r_100\_ .marker{fill:rgb(175, 175, 175);stroke:rgb(175, 175, 175);}#chatgpt-mermaid-\_r_100\_ .marker.cross{stroke:rgb(175, 175, 175);}#chatgpt-mermaid-\_r_100\_ svg{font-family:-apple-system-body,ui-sans-serif,-apple-system,system-ui,"Segoe UI",Helvetica,"Apple Color Emoji",Arial,sans-serif,"Segoe UI Emoji","Segoe UI Symbol";font-size:16px;}#chatgpt-mermaid-\_r_100\_ p{margin:0;}#chatgpt-mermaid-\_r_100\_ defs [id$="-barbEnd"]{fill:rgb(175, 175, 175);stroke:rgb(175, 175, 175);}#chatgpt-mermaid-\_r_100\_ g.stateGroup text{fill:rgb(31, 78, 148);stroke:none;font-size:10px;}#chatgpt-mermaid-\_r_100\_ g.stateGroup text{fill:rgb(237, 237, 237);stroke:none;font-size:10px;}#chatgpt-mermaid-\_r_100\_ g.stateGroup .state-title{font-weight:bolder;fill:rgb(237, 237, 237);}#chatgpt-mermaid-\_r_100\_ g.stateGroup rect{fill:rgb(9, 23, 44);stroke:rgb(31, 78, 148);}#chatgpt-mermaid-\_r_100\_ g.stateGroup line{stroke:rgb(175, 175, 175);stroke-width:1;}#chatgpt-mermaid-\_r_100\_ .transition{stroke:rgb(175, 175, 175);stroke-width:1;fill:none;}#chatgpt-mermaid-\_r_100\_ .stateGroup .composit{fill:transparent;border-bottom:1px;}#chatgpt-mermaid-\_r_100\_ .stateGroup .alt-composit{fill:#e0e0e0;border-bottom:1px;}#chatgpt-mermaid-\_r_100\_ .state-note{stroke:rgb(58, 132, 63);fill:rgb(48, 48, 48);}#chatgpt-mermaid-\_r_100\_ .state-note text{fill:rgb(237, 237, 237);stroke:none;font-size:10px;}#chatgpt-mermaid-\_r_100\_ .stateLabel .box{stroke:none;stroke-width:0;fill:rgb(9, 23, 44);opacity:0.5;}#chatgpt-mermaid-\_r_100\_ .edgeLabel .label rect{fill:rgb(9, 23, 44);opacity:0.5;}#chatgpt-mermaid-\_r_100\_ .edgeLabel{background-color:rgb(0, 0, 0);text-align:center;}#chatgpt-mermaid-\_r_100\_ .edgeLabel p{background-color:rgb(0, 0, 0);}#chatgpt-mermaid-\_r_100\_ .edgeLabel rect{opacity:0.5;background-color:rgb(0, 0, 0);fill:rgb(0, 0, 0);}#chatgpt-mermaid-\_r_100\_ .edgeLabel .label text{fill:rgb(237, 237, 237);}#chatgpt-mermaid-\_r_100\_ .label div .edgeLabel{color:rgb(237, 237, 237);}#chatgpt-mermaid-\_r_100\_ .stateLabel text{fill:rgb(237, 237, 237);font-size:10px;font-weight:bold;}#chatgpt-mermaid-\_r_100\_ .node circle.state-start{fill:rgb(175, 175, 175);stroke:rgb(175, 175, 175);}#chatgpt-mermaid-\_r_100\_ .node .fork-join{fill:rgb(175, 175, 175);stroke:rgb(175, 175, 175);}#chatgpt-mermaid-\_r_100\_ .node circle.state-end{fill:rgb(31, 78, 148);stroke:transparent;stroke-width:1.5;}#chatgpt-mermaid-\_r_100\_ .end-state-inner{fill:transparent;stroke-width:1.5;}#chatgpt-mermaid-\_r_100\_ .node rect{fill:rgb(9, 23, 44);stroke:rgb(31, 78, 148);stroke-width:1px;}#chatgpt-mermaid-\_r_100\_ .node polygon{fill:rgb(9, 23, 44);stroke:rgb(31, 78, 148);stroke-width:1px;}#chatgpt-mermaid-\_r_100\_ [id$="-barbEnd"]{fill:rgb(175, 175, 175);}#chatgpt-mermaid-\_r_100\_ .statediagram-cluster rect{fill:rgb(9, 23, 44);stroke:rgb(31, 78, 148);stroke-width:1px;}#chatgpt-mermaid-\_r_100\_ .cluster-label,#chatgpt-mermaid-\_r_100\_ .nodeLabel{color:rgb(237, 237, 237);}#chatgpt-mermaid-\_r_100\_ .statediagram-cluster rect.outer{rx:5px;ry:5px;}#chatgpt-mermaid-\_r_100\_ .statediagram-state .divider{stroke:rgb(31, 78, 148);}#chatgpt-mermaid-\_r_100\_ .statediagram-state .title-state{rx:5px;ry:5px;}#chatgpt-mermaid-\_r_100\_ .statediagram-cluster.statediagram-cluster .inner{fill:transparent;}#chatgpt-mermaid-\_r_100\_ .statediagram-cluster.statediagram-cluster-alt .inner{fill:rgb(48, 48, 48);}#chatgpt-mermaid-\_r_100\_ .statediagram-cluster .inner{rx:0;ry:0;}#chatgpt-mermaid-\_r_100\_ .statediagram-state rect.basic{rx:5px;ry:5px;}#chatgpt-mermaid-\_r_100\_ .statediagram-state rect.divider{stroke-dasharray:10,10;fill:rgb(48, 48, 48);}#chatgpt-mermaid-\_r_100\_ .note-edge{stroke-dasharray:5;}#chatgpt-mermaid-\_r_100\_ .statediagram-note rect{fill:rgb(48, 48, 48);stroke:rgb(58, 132, 63);stroke-width:1px;rx:0;ry:0;}#chatgpt-mermaid-\_r_100\_ .statediagram-note rect{fill:rgb(48, 48, 48);stroke:rgb(58, 132, 63);stroke-width:1px;rx:0;ry:0;}#chatgpt-mermaid-\_r_100\_ .statediagram-note text{fill:rgb(237, 237, 237);}#chatgpt-mermaid-\_r_100\_ .statediagram-note .nodeLabel{color:rgb(237, 237, 237);}#chatgpt-mermaid-\_r_100\_ .statediagram .edgeLabel{color:red;}#chatgpt-mermaid-\_r_100\_ [id$="-dependencyStart"],#chatgpt-mermaid-\_r_100\_ [id$="-dependencyEnd"]{fill:rgb(175, 175, 175);stroke:rgb(175, 175, 175);stroke-width:1;}#chatgpt-mermaid-\_r_100\_ .statediagramTitleText{text-anchor:middle;font-size:18px;fill:rgb(237, 237, 237);}#chatgpt-mermaid-\_r_100\_ [data-look="neo"].statediagram-cluster rect{fill:rgb(9, 23, 44);stroke:url(#chatgpt-mermaid-\_r_100\_-gradient);stroke-width:1;}#chatgpt-mermaid-\_r_100\_ [data-look="neo"].statediagram-cluster rect.outer{rx:5px;ry:5px;filter:drop-shadow( 1px 2px 2px rgba(185,185,185,1));}#chatgpt-mermaid-\_r_100\_ .node .neo-node{stroke:rgb(31, 78, 148);}#chatgpt-mermaid-\_r_100\_ [data-look="neo"].node rect,#chatgpt-mermaid-\_r_100\_ [data-look="neo"].cluster rect,#chatgpt-mermaid-\_r_100\_ [data-look="neo"].node polygon{stroke:url(#chatgpt-mermaid-\_r_100\_-gradient);filter:drop-shadow( 1px 2px 2px rgba(185,185,185,1));}#chatgpt-mermaid-\_r_100\_ [data-look="neo"].swimlane.cluster rect{filter:none;}#chatgpt-mermaid-\_r_100\_ [data-look="neo"].node path{stroke:url(#chatgpt-mermaid-\_r_100\_-gradient);stroke-width:1px;}#chatgpt-mermaid-\_r_100\_ [data-look="neo"].node .outer-path{filter:drop-shadow( 1px 2px 2px rgba(185,185,185,1));}#chatgpt-mermaid-\_r_100\_ [data-look="neo"].node .neo-line path{stroke:rgb(31, 78, 148);filter:none;}#chatgpt-mermaid-\_r_100\_ [data-look="neo"].node circle{stroke:url(#chatgpt-mermaid-\_r_100\_-gradient);filter:drop-shadow( 1px 2px 2px rgba(185,185,185,1));}#chatgpt-mermaid-\_r_100\_ [data-look="neo"].node circle .state-start{fill:#000000;}#chatgpt-mermaid-\_r_100\_ [data-look="neo"].icon-shape .icon{fill:url(#chatgpt-mermaid-\_r_100\_-gradient);filter:drop-shadow( 1px 2px 2px rgba(185,185,185,1));}#chatgpt-mermaid-\_r_100\_ [data-look="neo"].icon-shape .icon-neo path{stroke:url(#chatgpt-mermaid-\_r_100\_-gradient);filter:drop-shadow( 1px 2px 2px rgba(185,185,185,1));}#chatgpt-mermaid-\_r_100\_ :root{--mermaid-font-family:-apple-system-body,ui-sans-serif,-apple-system,system-ui,"Segoe UI",Helvetica,"Apple Color Emoji",Arial,sans-serif,"Segoe UI Emoji","Segoe UI Symbol";}INICIALIZACAOAGUARDANDOESCANEAMENTOAGUARDANDO_PISTAINSERCAOVALIDACAOSUCESSOERROFALHASensor prontoIniciar partidaQuatro amostras lidasRegra recebidaQuatro amostras inseridasOrdem corretaOrdem incorretaTentativas restantesLimite de tentativasPróxima rodada ou reinícioReinício autorizadoTimeout e regra padrão

Cada estado deverá controlar quais entradas são aceitas. Por exemplo, não será possível validar uma combinação antes de completar o escaneamento e receber a regra.

## 5. Implementação do sensor

Essa é a parte tecnicamente mais importante do projeto.

### Comunicação com a ESP32

O TCS34725 utiliza I²C.

| TCS34725 | ESP32                                 |
| -------- | ------------------------------------- |
| VIN      | Alimentação compatível com o breakout |
| GND      | GND                                   |
| SDA      | GPIO SDA configurado                  |
| SCL      | GPIO SCL configurado                  |

Confiram a tensão aceita pela placa específica do sensor. A TTGO T-Display possui pinos que podem variar conforme a versão; não assumam que os GPIOs I²C são iguais em todas elas.

### Processo de leitura

A leitura deverá seguir este procedimento:

1. Aguardar o cartão ser posicionado.
2. Realizar várias leituras consecutivas.
3. Descartar valores inválidos ou saturados.
4. Calcular a média ou mediana das amostras válidas.
5. Normalizar os canais RGB.
6. Armazenar os dados da amostra.

A normalização pode ser feita assim:

\\[ R_n=\frac{R}{R+G+B} \\]

\\[ G_n=\frac{G}{R+G+B} \\]

\\[ B_n=\frac{B}{R+G+B} \\]

Também é interessante armazenar o canal Clear, que representa a intensidade total de luz detectada.

### Calibração

Antes de desenvolver o jogo completo, façam um pequeno programa que mostre as leituras do sensor no monitor serial.

Coletem pelo menos 20 leituras de cada cartão, mantendo:

- A mesma iluminação.
- A mesma distância.
- A mesma orientação.
- O mesmo tempo de estabilização.

Depois, estabeleçam uma referência para cada cartão.

Na segunda leitura, o ESP32 poderá comparar a amostra com as referências salvas e identificar qual cartão foi apresentado.

Uma abordagem melhor que usar limites fixos de RGB é calcular a distância entre a leitura atual e as referências calibradas, por exemplo:

\\[ d=\sqrt{(R_n-R_r)^2+(G_n-G_r)^2+(B_n-B_r)^2} \\]

O cartão correspondente será aquele com menor distância, desde que esteja dentro de uma tolerância definida nos testes. Se estiver longe de todas as referências, o sistema deverá pedir uma nova leitura.

Cuidado: vermelho, amarelo, verde e azul são exemplos de cores que podem ser separadas, mas o sucesso dependerá das amostras físicas e da calibração.

## 6. Comunicação MQTT

O Grupo 1 é responsável pela especificação coletiva do protocolo. Vocês deverão alinhar os tópicos abaixo com a central antes da integração.

Sugestão de estrutura:

| Tópico              | Direção  | Finalidade                |
| ------------------- | -------- | ------------------------- |
| `ktne/game/start`   | Receber  | Iniciar partida           |
| `ktne/game/end`     | Receber  | Encerrar partida          |
| `ktne/color/clue`   | Receber  | Receber regra cromática   |
| `ktne/color/state`  | Publicar | Informar estado do módulo |
| `ktne/color/result` | Publicar | Informar sucesso ou falha |

### Exemplo de mensagem recebida

O módulo de sequência poderia publicar uma pista para o cofre:

```
{
  "module": "sequence",
  "game_id": "001",
  "rule": "BLUE_ASCENDING"
}
```

O módulo de vocês receberia essa informação e configuraria a regra do desafio.

### Exemplo de resultado publicado

```
{
  "module": "color",
  "game_id": "001",
  "status": "success",
  "attempts": 1
}
```

Sugiro que vocês também implementem:

- Identificador da partida (`game_id`), para ignorar mensagens antigas.
- Verificação de mensagens inválidas.
- Reconexão automática ao broker.
- Tratamento de mensagens duplicadas.
- Timeout para recebimento da pista.
- Publicação de estado quando o módulo ficar pronto.

O módulo não deve ficar travado se o Wi-Fi cair. Ele deve continuar controlando suas funções locais e sinalizar a indisponibilidade de comunicação.

## 7. Interface do display

A TTGO T-Display tem uma tela pequena, então é importante evitar informações excessivas.

Sugestão de telas:

COFRE CROMÁTICO

# AGUARDANDO

SENSOR: OK

Tela inicial

ESCANEANDO 02/04

# VERDE

R: 0.18 G: 0.62 B: 0.20

Leitura da amostra

REGRA RECEBIDA

## AZUL

ORDEM CRESCENTE

Instrução do puzzle

RESULTADO

# SUCESSO!

COFRE DESBLOQUEADO

Conclusão

Representações conceituais das telas, não capturas da interface real.

## 8. Divisão do trabalho entre Bruno e Ivan

Uma divisão possível para trabalhar em paralelo:

| Integrante | Responsabilidades                                               |
| ---------- | --------------------------------------------------------------- |
| Bruno      | Sensor TCS34725, calibração, classificação das cores e circuito |
| Ivan       | Máquina de estados, regras do puzzle, display e MQTT            |
| Ambos      | Montagem física, integração, testes e documentação              |

A divisão não precisa ser rígida: ambos devem entender o funcionamento completo para conseguir apresentar e explicar o projeto.

## 9. Cronograma de desenvolvimento

Eu dividiria o projeto em seis entregas incrementais. A ideia é sempre ter algo funcionando ao final de cada etapa.

Checklist de desenvolvimento

0/6 concluídas

1\. Montagem e teste do sensor

Conectar o TCS34725, testar I²C e exibir RGB/Clear no Serial.

2\. Calibração das amostras

Criar os quatro cartões, coletar leituras e implementar reconhecimento.

3\. Puzzle local

Implementar escaneamento, regras de ordenação e validação.

4\. Interface e estados

Criar as telas, botões, tentativas, erros e sucesso.

5\. Integração MQTT

Receber pistas, identificar partidas e publicar resultados.

6\. Testes e documentação

Testar standalone, broker, falhas e demonstração integrada.

### Estimativa de esforço

| Etapa                      | Tempo estimado |
| -------------------------- | -------------- |
| Montagem e teste do sensor | 2–3 horas      |
| Calibração                 | 2–4 horas      |
| Puzzle local               | 3–5 horas      |
| Interface e estados        | 2–4 horas      |
| MQTT                       | 2–4 horas      |
| Testes e documentação      | 3–4 horas      |
| Total                      | 14–24 horas    |

Estimativa para uma primeira implementação funcional, não incluindo possíveis problemas de hardware ou integração.

## 10. Critérios de conclusão e testes

Antes da apresentação, vocês devem conseguir demonstrar:

| Teste                | Resultado esperado                                   |
| -------------------- | ---------------------------------------------------- |
| Inicialização        | Sensor reconhecido pela ESP32                        |
| Leitura              | Quatro cartões identificados corretamente            |
| Calibração           | Leituras consistentes em condições controladas       |
| Regra crescente      | Combinação calculada corretamente                    |
| Regra decrescente    | Combinação calculada corretamente                    |
| Combinação correta   | Cofre desbloqueado                                   |
| Combinação incorreta | Erro e penalidade                                    |
| MQTT                 | Recebimento de pistas e publicação de resultados     |
| Desconexão Wi-Fi     | Módulo continua funcionando localmente               |
| Reinício             | Novo desafio pode ser iniciado sem reiniciar a placa |

## 11. Melhorias futuras

Depois que a versão básica estiver funcionando, vocês podem acrescentar:

- Regras aleatórias: a cada partida, o sistema escolhe uma regra diferente.
- Dificuldade progressiva: aumentar a quantidade de cartões ou limitar o tempo de leitura.
- Pistas limitadas: o jogador pode solicitar uma dica, mas isso consome tempo.
- Múltiplas rodadas: o cofre possui mais de uma combinação para ser desbloqueado.
- Cartões falsos: introduzir amostras com cores semelhantes para dificultar a identificação.
- Penalidades: cada combinação errada reduz o tempo restante da partida.

## 12. Escopo recomendado para a primeira versão

Para não complicar demais o trabalho, eu estabeleceria este escopo mínimo:

MVP — primeira versão funcional

1. Quatro cartões: vermelho, verde, azul e amarelo.
2. Sensor TCS34725 fixo em uma estrutura de leitura.
3. Reconhecimento dos quatro cartões por calibração.
4. Quatro regras de ordenação: R, G, B e luminosidade.
5. Recebimento da regra via MQTT.
6. Releitura física dos cartões na ordem escolhida.
7. Validação automática da combinação.
8. Publicação de sucesso ou falha.
9. Funcionamento standalone com regra padrão.

Uma decisão técnica importante: não recomendo gerar uma ordem aleatória dos cartões sem garantir que as leituras sejam suficientemente distintas. Primeiro validem a confiabilidade dos cartões e do sensor. Depois implementem a aleatoriedade.

## 13. Repositório e documentação

O código deverá ser organizado e versionado no GitHub de vocês. Recomendo criar um README contendo:

- Objetivo e funcionamento do cofre cromático.
- Lista de componentes.
- Diagrama de ligação do TCS34725.
- Bibliotecas utilizadas.
- Configuração Wi-Fi e MQTT (sem publicar senhas no repositório).
- Descrição da máquina de estados.
- Especificação dos tópicos MQTT.
- Instruções para compilar e executar.
- Fotos e vídeos da montagem.

O repositório fornecido no trabalho é [KTNE-ESP32](https://github.com/GroosL/KTNE-ESP32?utm_source=chatgpt.com).
