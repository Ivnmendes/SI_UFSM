# Exercícios 21/09

1. Segundo Goldbach, qualquer número par maior que 2 pode ser o resultado da soma de dois números
primos. Faça um programa que leia vários números inteiros e positivos N enquanto forem pares e, para
cada número N, chame uma função, passando N como parâmetro, que imprima todos os arranjos (a
ordem importa) possíveis entre dois números primos cuja soma seja igual ao número N.
2. Faça um programa que leia um conjunto de valores inteiros positivos. Usar -1 como marca de parada.
Dentre os valores lidos, o programa deve imprimir:
    - O menor valor dentre os maiores que 100 e menores que 1000 (não incluindo 100 e 1000);
    - A média dos valores dentre os maiores que 100 e menores que 1000;
    - A soma dos valores dentre os maiores que 100 e menores que 1000;
    - A soma de todos os valores lidos.
3. Faça um programa que leia um número inteiro de 3 dígitos. A seguir, o programa deve chamar uma
função, passando o número como parâmetro. A função deve imprimir se o algarismo da casa das
centenas é par ou ímpar. O programa deve ser repetido enquanto a entrada for válida.
4. Faça um programa que leia um número indeterminado de valores e, para cada valor, chame uma função,
passando o valor como parâmetro. A função deve calcular e exiba todos os seus divisores do número
recebido. O programa termina quando o usuário, ao ser perguntado, responder que deseja encerrar.
5. Faça um programa que leia uma sequência de números terminada por 0 e imprima o número que for
múltiplo de sua posição na sequência.
    - Ex.:    
    ```
        valores lidos:     3    7   8   16
        posição:           1    2   3   4
        saída:             3 e 16
    ```
6. Faça um programa que calcule a média dos números pares digitados pelos usuário. O programa deve
encerrar a entrada quando encontrar o valor 0. Implemente: (a) uma versão com while; (b) uma versão
com do-while.
7. Faça um programa que leia dois números inteiros. A seguir, chame uma função que calcule e exiba o
quociente e o resto da divisão dos números lidos, usando **apenas** as operações de soma e/ou subtração.
8. Faça um programa que encontre todos os pares de números amigáveis entre 1 e 100000 (excluindo os
mesmos). Um par de números é amigável quando cada um deles é igual à soma dos divisores do outro.
    - Ex.: 220 e 284 são amigos, pois:
        - os divisores de 220 são 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 e 110, cuja soma é 284
        - os divisores de 284 são 1, 2, 4, 71 e 142, cuja soma é 220
9. Faça um programa que leia três valores inteiros **n**, **a** e **b** e passe-os como parâmetros para uma função. A
função deve exibir os **n** primeiros múltiplos simultâneos de **a** e **b**.
10. Faça um programa que leia um número inteiro positivo **n** (onde n>1) e determine a sua decomposição
em fatores primos, calculando também a multiplicidade de cada fator.
    - Ex.: para n = 36, a decomposição será: fator 2 multiplicidade 2 fator 3 multiplicidade 2
11. Faça um programa que imprima a tabuada de **x** até **y**, onde **x** e **y** devem ser digitados pelo usuário. A
saída do programa deve ser como segue:
~~~c
    Digite os valores para x e y: 5 15

    Tabuada de multiplicacao!
    ------------------------------------------------------------
    |   |   5|   6|   7|   8|   9|  10|  11|  12|  13|  14|  15|
    ------------------------------------------------------------
    | 5 |  25|  30|  35|  40|  45|  50|  55|  60|  65|  70|  75|
    | 6 |  30|  36|  42|  48|  54|  60|  66|  72|  78|  84|  90|
    | 7 |  35|  42|  49|  56|  63|  70|  77|  84|  91|  98| 105|
    | 8 |  40|  48|  56|  64|  72|  80|  88|  96| 104| 112| 120|
    | 9 |  45|  54|  63|  72|  81|  90|  99| 108| 117| 126| 135|
    |10 |  50|  60|  70|  80|  90| 100| 110| 120| 130| 140| 150|
    |11 |  55|  66|  77|  88|  99| 110| 121| 132| 143| 154| 165|
    |12 |  60|  72|  84|  96| 108| 120| 132| 144| 156| 168| 180|
    |13 |  65|  78|  91| 104| 117| 130| 143| 156| 169| 182| 195|
    |14 |  70|  84|  98| 112| 126| 140| 154| 168| 182| 196| 210|
    |15 |  75|  90| 105| 120| 135| 150| 165| 180| 195| 210| 225|
    ------------------------------------------------------------
~~~
12. Você está aprendendo a jogar xadrez, mas tem dificuldade em saber para qual direção pode mover sua
Torre. Sabemos que um tabuleiro de xadrez é composto por 8 linhas e 8 colunas e que a Torre se move
ortogonalmente, ou seja, pelas linhas (horizontais) e pelas colunas (verticais). Faça um programa que leia
o número da linha e da coluna que indicam a posição de sua Torre. A seguir, o programa deve imprimir
quais são os possíveis movimentos da Torre. Utilize "−" para indicar uma casa para a qual a Torre não
pode ser movida e "x" para indicar uma casa para a qual ela pode ser movida. A saída do programa deve
ser como segue:
~~~c
    Movimentos de uma Torre no xadrez!
    Digite a linha e a coluna em que a Torre se encontra: 6 3

    Movimentos possiveis:
         1    2    3    4    5    6    7    8
      -----------------------------------------
    1 |    -    -    *    -    -    -    -    -
    2 |    -    -    *    -    -    -    -    -
    3 |    -    -    *    -    -    -    -    -
    4 |    -    -    *    -    -    -    -    -
    5 |    -    -    *    -    -    -    -    -
    6 |    *    *    *    *    *    *    *    *
    7 |    -    -    *    -    -    -    -    -
    8 |    -    -    *    -    -    -    -    -
~~~
