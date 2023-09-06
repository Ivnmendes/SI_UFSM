# Exercícios aula 05/09

1. Faça um programa que chame uma função que leia um número correspondente ao mês atual e 4 dígitos da placa de um veículo. Através do número finalizador da placa (algarismo da casa das unidades) determine e informe quando vence o IPVA do veículo:

    Final|Mês
    :---:|:--:
    1|Janeiro
    2|Fevereiro
    3|Março
    4|Abril
    5|Maio
    6|Junho
    7|Julho
    8|Agosto
    9|Setembro
    10|Outubro

2. Detecção de colisão é uma das operações mais comuns (e importantes) em jogos eletrônicos. O objetivo, basicamente, é verificar se dois objetos quaisquer colidiram, ou seja, se a intersecção entre eles é diferente de vazio. Isso pode ser usado para saber se duas naves colidiram, se um monstro bateu numa parede, se um personagem pegou um item, etc. Para facilitar as coisas, muitas vezes os objetos são aproximados por figuras geométricas simples (esferas, paralelepípedos, triângulos etc). Neste problema, os objetos são aproximados por retângulos num plano. Um retângulo é definido pelas coordenadas de dois pontos no plano: o canto inferior esquerdo tem coordenadas (x<sub>0</sub>,y<sub>0</sub>) e o canto superior direito tem coordenadas (x<sub>1</sub>,y<sub>1</sub>).

    * Restrições:
    * 0 ≤ x0 < x1 ≤ 1.000.000
    * 0 ≤ y0 < y1 ≤ 1.000.000

    * Entrada: A entrada contém duas linhas. Cada linha contém quatro inteiros x0, y0, x1, y1, representando as coordenadas do canto inferior esquerdo e do canto superior direito de um retângulo. Os lados do retângulo são sempre paralelos aos eixos x e y.
    * Saída: Deve imprimir uma única linha, contendo o número 1 (um) caso haja intersecção entre os retângulos ou o número 0 (zero) caso não haja intersecção.

    Faça um programa que chame uma função para resolver o problema acima. A função deve realizar
    tanto a entrada de dados (leitura dos 4 valores inteiros), como a saída de dados (impressão do
    resultado da verificação de intersecção).

    Exemplos:

    Entrada|saída
    :-----:|:---:
    0 0 1 1 1 1 2 2|1
    0 0 2 2 1 1 3 3|1
    0 0 1 1 2 2 3 3|0


3. As tarifas de um estacionamento são as seguintes:
    * 1ª e 2ª hora - R$1,00 cada
    * 3ª e 4ª hora - R$1,40 cada
    * 5ª e seguintes - R$2,00 cada

    O número de horas a pagar é sempre inteiro e arredondado por    excesso. Assim, quem estacionar durante 61 minutos pagará por   duas horas, que é o mesmo que pagaria se tivesse permanecido    120 minutos. Os momentos de chegada ao estacionamento e saída   deste são apresentados na forma de pares de inteiros,   representando horas e minutos. Por exemplo, o par 12 50     representará “dez para a uma da tarde”. Faça um programa que    leia os horários de chegada e saída, passe-os para uma função   que calcule e imprima valor a ser pago pelo estacionamento.     Deverá haver validação de dados. Admite-se que a chegada e a    saída se dão com intervalo não superior a 24 horas. Portanto,   se uma dada hora de chegada for superior à da partida, isso     não é uma situação de erro, pois significa que a partida    ocorreu no dia seguinte ao da chegada.

4. O dono de uma empresa de venda de passagens aéreas decidiu aumentar seu negócio realizando fretes turísticos por todo o Brasil. Para isso ele deve calcular o preço do diesel de acordo com a distância que a van vai andar. Faça um programa que chame uma função que leia o número de km que deverão ser rodados (entre 0 e 900 km), e imprima o gasto em diesel que ele deverá ter. Levando em consideração que:
    * O tanque da van suporta 90 litros de diesel;
    * Ela roda 10 km com 1 litro de diesel;
    * O preço do litro do diesel é R$ 2,50;
    * O posto que a van será abastecida está fazendo uma promoção. Se forem abastecidos mais de 45 litros, o preço do litro sai por R$ 2,30.

* Entrada: A entrada contém um inteiro que indica os km que a van precisará viajar. Saída: A saída consiste em imprimir o preço de diesel que será gasto.

    * Exemplo:
    Entrada|Saída
    :--:|:--:
    500|R$115,00

5.  Utilize o comando switch e o tipo ‘char’ para fazer um programa que calcula as áreas das seguintes figuras geométricas:
    * ‘q’ - Área do quadrado
    * ‘r’ - Área do retângulo
    * ‘t’ - Área do triângulo
    * ‘p’ - Área trapézio

    Baseado na escolha do usuário, você deverá ler os valores necessários para fazer os cálculos, imprimir o nome da figura escolhida e o valor da área. As opções de figuras geométricas devem estar dispostas em um switch e cada uma delas implementada por uma função. Cada função irá fazer a leitura da entrada e a impressão do resultado.

6. Deseja-se organizar fotos em um álbum. Para economizar páginas do álbum, deve-se colar duas fotos por página do álbum. Como as fotos são retangulares, as fotos podem ser coladas giradas (mas sempre com lados paralelos aos da página do álbum), mas elas devem sempre ficar inteiramente contidas no interior da página, e não devem se sobrepor. Em geral, das muitas formas de posicionar as fotos do álbum só algumas (ou nenhuma) satisfazem estas restrições, então pode ser difícil decidir se é possível colar as duas fotos em uma mesma página do álbum. Faça um programa que chame uma função que leia a largura e altura da página do álbum, a largura e altura da foto 1 e a altura e largura da foto 2. A seguir, a função deve verificar se é possível colar as duas fotos na página do álbum. Esse resultado deve ser retornado para a função main, que irá realizar a impressão da saída. Por exemplo, cada página pode ser 5x7, e duas fotos são 3x4. Nesse caso, é possível colar as duas fotos:

* Ex.:
    * Entrada
        * 7 5
        * 3 4
        * 3 4
    * Saída
        * S

    * Entrada
        * 13 8
        * 4 9
        * 6 5
    * Saída
        * N

7. Em uma danceteria o preço da entrada sofre variações. Domingo, Segunda e Terça (‘D’, ‘2’, ‘3’), ela oferece um desconto de 25% no preço normal de entrada. Nos dias de música ao vivo, o preço da entrada é acrescido em 15% em relação ao preço normal. Faça um programa que chame uma função que leia o preço normal da entrada, o dia da semana (‘D’, ‘2’, ‘3, ‘4’, ‘5’, ‘6’, ‘S’), e se é dia de música ao vivo (‘S’ ou ‘N’). A função deve calcular e retornar o preço a ser pago pela entrada, que deve ser impresso pela função main.

8. Em época de inflação alta, a empresa KKK tem uma política de juros para compra de produtos a prazo (em dias) conforme mostrado abaixo:
    Prazo|Juros
    :---:|:-----:
    1-3|0
    4-7|0,5%
    8-12|1,5%
    13-20|3%

    Faça um programa que leia o valor de uma compra e o prazo de pagamento. A seguir, o programa deve chamar uma função, passando esses valores como parâmetros, que deve calcular o valor a ser gasto com o produto. Esse valor deve ser retornado para a função main, que irá imprimir como saída
