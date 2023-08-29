# Exercícios aula 29/08

1. Para incentivar a economia de água, uma empresa de abastecimento alterou os preços de seu fornecimento de modo que, proporcionalmente, os clientes que consumirem menos água paguem menos pelo metro cúbico. Todo cliente paga mensalmente uma assinatura de R\$ 7,00, que inclui uma franquia de 10m<sup>3</sup> de água. Isto é, para qualquer consumo entre 0 e 10m<sup>3</sup>, o consumidor paga a mesma quantia de R\$ 7,00 (note que o valor da assinatura deve ser pago mesmo que o consumidor não tenha consumido água). Acima de 10m<sup>3</sup>, cada metro cúbico subsequente tem um valor diferente, dependendo da faixa de consumo, conforme tabela abaixo. São sobradas apenas quantidades inteiras de metros cúbicos.

    Faixa de Consumo (m<sup>3</sup>) | Preço (por m<sup>3</sup>)
    :-------------------------------:|:------------------------:
    Até 10|Incluído na franquia
    11 a 30|R\$1,00
    31 a 100|R\$2,00
    101 em diante|R\$5,00

    Assim, por exemplo, se o consumo foi de 120m<sup>3</sup>, o valor da conta é:
    * R\$ 7,00 da assinatura básica;
    * R\$ 20,00 pelo consumo no intervalo 11-30m<sup>3</sup>;
    * R\$ 140,00 pelo consumo no intervalo 31-100m<sup>3</sup>;
    * R\$ 100,00 pelo consumo no intervalo 101-120m<sup>3</sup>;

    Logo, o valor da conta de água é R\$ 267,00.

    Faça um programa que leia o consumo de uma residência, em m<sup>3</sup>, calcule e imprima o valor de sua conta de água.

2. O móbile de Maria é composto por três hastes como mostra a figura abaixo. Para que ele esteja completamente equilibrado, com todas as hastes na horizontal, os pesos das quatro bolas A, B, C e D têm que satisfazer todas as seguintes condições:
    * A = B + C + D
    * B + C = D
    * B = C

    Faça um programa que leia os pesos das quatro bolas e informe se o móbile está ou não completamente equilibrado.

3. A ORB (Organização Regional de Bocha) numa tentativa de aumentar a popularidade da competição decidiu chamar para a Grande Final Mundial o campeão e o vice-campeão de cada cidade, ao invés de apenas o primeiro lugar. A ORB não armazenou quem foi o segundo classificado, mas armazenou a pontuação de todos competidores - que foram apenas três, devido ao sucesso do campeonato. Sabe-se também que as pontuações de todos jogadores foram diferentes, de forma que não ocorreu empate entre nenhum deles. Resta agora descobrir quem foi o vice-campeão. Faça um programa que leia as pontuações dos três competidores e informe a pontuação do vice-campeão.

4. Faça um programa que leia o preço do litro de álcool, o preço do litro de gasolina e os quilômetros por litro que um carro bi-combustível realiza com cada um desses combustíveis e determine se é mais econômico abastecer o carro com álcool ou gasolina. No caso de não haver diferença de custo entre abastecer com álcool ou gasolina, o motorista prefere utilizar gasolina.

5. Os computadores foram inventados para realizar cálculos rapidamente e atendem a esse requisito de maneira extraordinária. Porém, nem sempre o computador consegue representar todos os números dentro de sua memória. Caso alguma conta executada pelo computador dê um resultado acima de sua capacidade, ocorre overflow, que é quando o computador faz uma conta e o resultado não pode ser representado, por ser maior do que o valor máximo permitido. Por exemplo, se um computador só pode representar números menores do que 1023 e mandamos ele executar a conta 1022 + 5, vai ocorrer overflow. Faça um programa que leia o maior número que um computador consegue representar. Em seguida, leia um valor inteiro, seguido de um espaço em branco, seguido de um caractere (que pode ser ‘+’ ou ‘*’, representando os operadores de adição e multiplicação, respectivamente), seguido de um espaço em branco, seguido de outro inteiro. Essa linha representa uma expressão (A+B ou A*B). O programa deve imprimir a palavra “Overflow”, se o resultado da expressão causar um overflow, ou “Ok”, caso contrário.

6. Depois de fazer o primeiro contato com uma civilização extraterrestre (os termopilitas), você ficou encarregado de fazer a conversão de datas entre as duas civilizações. Por coincidência o ano dos termopilitas tem a mesma duração do ano terrestre, mas é dividido de maneira diferente: a menor unidade de tempo é o blip, que dura 3 segundos terrestres. Quarenta blips fazem um tak, que é a próxima unidade. Quinze taks fazem um salek, e 30 saleks fazem um mazel. Oito mazels fazem um brat e 73 brats completam o ano inteiro. Faça um programa que ofereça um menu com as seguintes opções:
    * a) Converter de terrestre para termopilita: para essa opção, o programa deve ler uma data terrestre no formato dia mês hora min seg, calcular e imprimir a data no formato termopilita: brat mazel salek tak blip.
    * b) Converter de termopilita para terrestre: para essa opção, o programa deve ler uma data termopilita no formato brat mazel salek tak blip, calcular e imprimir a data no formato terrestre (dia mês hora min seg).
    * c) Construa uma tabela de conversões das unidades de tempo termopilitas, dizendo o quanto cada uma delas vale nas unidades terrestres. Exemplos de possíveis valores para constar na tabela:

        Tempo Terrestre | Tempo termopolita
        :--------------:|:------------------:
        30 segundos|?
        2 minutos|?
        30 minutos|?
        15 horas|?
        5 dias|?
        1 ano|?

7. Supondo o jogo Dois ou Um, utilizado para determinar um ganhador entre três ou mais jogadores. Onde cada jogador escolhe um valor entre dois ou um; a um comando (geralmente um dos competidores anuncia em voz alta "Dois ou... Um!"), todos os participantes mostram o valor escolhido, utilizando uma das mãos. O ganhador é aquele que tiver escolhido um valor diferente de todos os outros; se não há um jogador com valor diferente de todos os outros (por exemplo todos os jogadores escolhem dois, ou um grupo de jogadores escolhe dois e outro grupo escolhe um), não há ganhador. Ana, Bob e Caren são grandes amigos e jogam “Dois ou Um” a toda hora. Faça um programa que leia três inteiros A, B e C, indicando respectivamente os valores escolhidos por Ana, Bob e Caren, e determine se há um ganhador, e nesse caso imprima seu nome. Caso não haja vencedor, deve ser impresso o caractere ‘\*’.

    **Ex:**
    * Entrada 1 1 2 Saída **Caren**
    * Entrada 2 2 2 Saída **\***
    * Entrada 2 1 1 Saída **Ana**

8. Considere uma semi-quadra de tênis, a qual corresponde a um retângulo em que dois vértices têm coordenadas (0,0) e (432, 468), onde todos os números são em polegadas. Faça um programa que leia as coordenadas (X, Y) do ponto de contato da bola com o solo, e determine se uma bola bateu no solo dentro ou fora da semi-quadra. Note que se a bola bate na linha divisória ela é considerada uma bola dentro. O programa deve imprimir a informação se a bola caiu dentro ou fora da quadra.
