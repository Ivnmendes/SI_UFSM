# Programa com if-else

Você foi contratado pela empresa ZOXY para desenvolver um sistema para efetuar cálculos diversos utilizados pelos funcionários da empresa no dia a dia. Para auxiliar nessa tarefa, foi disponibilizada uma especificação detalhada de todos os menus e submenus a serem desenvolvidos, bem como as ações a serem executadas. Para facilitar a compreensão, a especificação foi dividida em etapas, cada qual correspondendo a uma funcionalidade.

**Etapa 1**: Criação do menu inicial do programa. No cabeçalho do menu, deve ser exibido o nome da empresa (‘ZOXY’) dentro de um retângulo demarcado por asteriscos (*). A seguir, devem ser exibidas para o usuário quatro opções e solicitada uma entrada em formato caractere, conforme segue:

```c
Menu Inicial
a. Validacao de data
b. Diferenca de horarios
c. Conversao de temperatura
d. Calculo de material
>Selecione uma opcao:_
```

As quatro opções possíveis devem aceitar tanto com caracteres minúsculos quanto maiúsculos (ex.: ‘A’ ou ‘a’, etc.). Se o usuário informar uma opção inválida, o programa deve exibir uma mensagem de erro e encerrar imediatamente.

**Etapa 2a**: Se o usuário selecionar a opção ‘a’, o programa exibe o título “A > Validação de data” e solicita três valores ao usuário, sendo eles “Dia”, “Mês” e “Ano”. Em seguida, o programa deve verificar se a data digitada é válida, considerando as seguintes premissas:
- Janeiro, março, maio, julho, agosto, outubro e dezembro sempre possuem 31 dias e os demais meses (com exceção de fevereiro) sempre possuem 30 dias; e
- Fevereiro possui 28 dias, exceto em anos bissextos, em que possui 29 dias. Um ano é bissexto se ele for divisível por 400 ou se ele for divisível por 4 e não por 100.

Se, por qualquer um dos motivos acima, a data digitada for inválida, o programa deve exibir uma mensagem de erro e encerrar imediatamente. Caso a data seja válida, o programa exibe um menu contendo três opções para a formatação da data e, com base na opção informada, formata a data e a exibe de acordo. Por fim, exibe uma mensagem de finalização (* fim *)

```c
A > Validacao de data
>Dia:29
>Mes:02
>Ano:2020
1. DD/MM/YYYY
2. YYYY-MM-DD
3. DD de [Mes] de YYYY
>Selecione uma opcao:_
<output
* fim *
```

No exemplo, o **output** varia de acordo com a opção selecionada, sendo:

- Opção 1: **29/02/2020**
- Opção 2: **2020-02-29**
- Opção 3: **29 de fevereiro de 2020**
- Para quaisquer outras opções, o programa exibe mensagem de erro e encerra imediatamente.

**Etapa 2b**: Se o usuário selecionar a opção ‘b’, o programa exibe o título “B > Diferença de horários” e solicita quatro valores ao usuário, sendo eles (em ordem): “Hora h1”, “Minuto m1”, “Hora h2”, “Minuto m2”. Considere que os inputs estão no mesmo fuso horário e em formato 24h. Em seguida, o programa calcula e exibe a diferença entre os horários informados (h1:m1 e h2:m2) de acordo com a opção de visualização selecionada pelo usuário (“Padrão”, “Minutos”, “Segundos” ou “Milissegundos”). **Atenção**: se o segundo horário informado (h2:m2) for menor ou igual ao primeiro horário (h1:m1), considera-se que eles ocorrem em dias diferentes (isso é, o segundo horário ocorre no dia d+1)

```c
B > Diferenca de horarios
>Hora h1:15
>Minuto m1:30
>Hora h2:14
>Minuto m2:00
1. Padrao
2. Minutos
3. Segundos
4. Milisegundos
>Selecione uma opcao:_
<Diferenca: output
* fim *
```

No exemplo, o **output** varia de acordo com a opção selecionada, sendo:

- Opção 1: **22 horas e 30 minutos**
- Opção 2: **1350m**
- Opção 3: **81000s**
- Opção 4: **81000000ms**
- Para quaisquer outras opções, o programa exibe mensagem de erro e encerra imediatamente.

**Etapa 2c**: Se o usuário selecionar a opção ‘c’, o programa exibe o título “C > Conversão de temperatura” e lê um valor real do usuário equivalente a uma temperatura em escala Celsius. Após, solicita uma escala para conversão (“Fahrenheit”, “Kelvin” ou “Rankine”), calcula e exibe a temperatura na escala escolhida. Considere as seguinte equivalências, onde ºC é uma temperatura em Celsius, ºF em Fahrenheit, K em Kelvin e ºR na escala Rankine:

- $(°C \cdot \dfrac{9}{5}) + 32 = °F$
- $(°C + 273.15 = K$
- $(°C \cdot \dfrac{9}{5}) + 491.67 = °R$

```c
C > Validacao de data
>Temperatura (°C): 37.5
1. Fahrenheit
2. Kelvin
3. Rankine
>Selecione uma opcao:_
<output
* fim *
```

No exemplo, o **output** varia de acordo com a opção selecionada, sendo:

- Opção 1: **37.5°C <-> 99.5°F**
- Opção 2: **37.5°C <-> 310.65K**
- Opção 3: **37.5°C <-> 559.17°R**
- Para quaisquer outras opções, o programa exibe mensagem de erro e encerra imediatamente.

**Etapa 2d**: Se o usuário selecionar a opção ‘d’, o programa exibe o título “D > Cálculo de material” e lê dois valores reais equivalentes à altura e ao comprimento (em metros) de uma parede qualquer. Em seguida, solicita ao usuário qual tipo de tijolo ele deseja utilizar como base para o cálculo e retorna o número de tijolos a serem necessários (arredondado para cima, quando aplicável) para cobrir a área dada pela altura e comprimento informados e o valor final da compra (arredondado para duas casas decimais). Considere os seguintes tipos de tijolos e suas respectivas dimensões (altura x comprimento) e o valor do milheiro de tijolos:

- 6 furos: 14cm * 19cm, R$ 400,00/milheiro
- 8 furos: 19cm * 19cm, R$ 780,50/milheiro
- 9 furos: 19cm * 29cm, R$ 899,99/milheiro

```c
C > Calculo de material
>Altura (m): 3.5
>Comprimento (m): 2.5
1. 6 furos
2. 8 furos
3. 9 furos
>Selecione uma opcao:_
<output
* fim *
```

No exemplo, o **output** varia de acordo com a opção selecionada, sendo:

- Opção 1: **329 unidades (R$ 131.60)**
- Opção 2: **243 unidades (R$ 189.66)**
- Opção 3: **159 unidades (R$ 143.10)**
- Para quaisquer outras opções, o programa exibe mensagem de erro e encerra imediatamente.

Orientações:
- **A interpretação da especificação do trabalho faz parte da avaliação**;
- O trabalho é individual;
- **Além do conteúdo de programação sequencial (entrada e saída, expressões, variáveis), somente pode ser usado o comando de seleção IF-ELSE**;
- O código deve estar organizado, indentado e obedecer criteriosamente à
especificação;
- Certifique-se de compilar e testar exaustivamente o programa antes do envio;
- Deve ser entregue **apenas o arquivo .c**, cujo nome deve ser: nomeAluno_ifelse.c (ex. mariana_ifelse.c). Trabalhos que não obedecerem essa regra serão desconsiderados;
- Não serão aceitos trabalhos entregues fora da plataforma Moodle;
- Trabalhos total ou parcialmente copiados receberão nota zero.
