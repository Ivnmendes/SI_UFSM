# Propostas de Aplicações IoT — Trabalho Final

**Disciplina:** Internet das Coisas  
**Curso:** Sistemas de Informação  
**Integrantes:** Bruno Henrique Bock e Ivan Mendes Martignago

## 1. QuizNet — Jogo de perguntas e respostas

**a) Nome da aplicação:** QuizNet.

**b) Descrição:** Jogo de perguntas e respostas inspirado no Kahoot e no Show do Milhão, com o objetivo de promover uma competição interativa entre participantes utilizando dispositivos ESP32.

**c) Funcionamento:** Um ESP32 atua como apresentador, exibindo perguntas e alternativas no display. Os demais dispositivos representam os jogadores, que selecionam suas respostas utilizando os botões físicos. O apresentador verifica as respostas, contabiliza os pontos e atualiza o placar ao final de cada rodada.

**d) Comunicação:** O MQTT será utilizado para distribuir as perguntas, receber as respostas dos jogadores e transmitir os resultados e o placar entre os dispositivos conectados à rede Wi-Fi.

**e) Recursos utilizados:** ESP32 TTGO T-Display, displays para exibição das perguntas e resultados, botões físicos para seleção das respostas, Wi-Fi para conexão à rede e MQTT para comunicação entre os dispositivos.

## 2. ESP Arena — Competição de reflexos

**a) Nome da aplicação:** ESP Arena.

**b) Descrição:** Competição de tempo de reação na qual os participantes devem pressionar um botão assim que um sinal visual aparecer no display. O objetivo é identificar o participante com o menor tempo de reação.

**c) Funcionamento:** Um ESP32 atua como árbitro e inicia as rodadas. Os dispositivos dos jogadores exibem um sinal visual em determinado momento e registram o tempo entre o sinal e o acionamento do botão. Os resultados são enviados ao árbitro, que compara os tempos e anuncia o vencedor.

**d) Comunicação:** O MQTT será utilizado para transmitir os comandos de início das rodadas, receber os tempos de reação dos jogadores e distribuir os resultados e a classificação da competição.

**e) Recursos utilizados:** ESP32 TTGO T-Display, displays para instruções e resultados, botões físicos para registrar as reações, Wi-Fi para conexão à rede e MQTT para comunicação entre os dispositivos. LEDs poderão ser utilizados opcionalmente para sinalização.

## 3. SmartControl — Controle remoto entre dispositivos

**a) Nome da aplicação:** SmartControl.

**b) Descrição:** Sistema de controle remoto no qual um ESP32 permite ajustar parâmetros de funcionamento de outro dispositivo conectado à rede, demonstrando o controle e o monitoramento de dispositivos IoT.

**c) Funcionamento:** Um ESP32 atua como controlador, permitindo ao usuário ajustar um parâmetro por meio de um potenciômetro ou botões. O valor é enviado a outro ESP32, que controla um atuador, como um LED, e informa seu estado atual. O controlador apresenta a configuração e o estado recebido em seu display.

**d) Comunicação:** O MQTT será utilizado para enviar comandos do controlador ao dispositivo receptor e transmitir o estado atualizado do receptor de volta ao controlador, permitindo acompanhar a execução dos comandos.

**e) Recursos utilizados:** ESP32 TTGO T-Display, displays para exibição dos parâmetros e estados, potenciômetro ou botões para ajustar os valores, LED como atuador, Wi-Fi para conexão à rede e MQTT para troca de comandos e informações entre os dispositivos.
