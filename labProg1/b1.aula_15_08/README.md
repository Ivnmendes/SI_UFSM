# Exercícios 15/08

1. Declare uma variável x como inteira. A seguir, atribua o valor 10 a x. Ao final, imprima x.
2. Declare uma variável inteira, leia um valor para ela e a imprima.
3. Declare uma variável inteira e uma variável real. A seguir, leia um número inteiro e um número real e os imprima. Utilize apenas 1 comando `scanf` (leitura das 2 variáveis) e 1 comando `printf` (escrita das 2 variáveis).
4. Declare uma variável como string. A seguir, leia uma palavra e a imprima. Por último, imprima novamente a palavra, colocando-a entre aspas. (obs.: com string, o especificador é `%s` e o `scanf` dispensa o `&`)
5. Leia seu primeiro nome e idade e os imprima, um em cada linha.
6. Declare 3 variáveis: uma inteira (x), uma real de precisão curta (y) e uma real de precisão longa (z). A seguir, leia valores para cada uma e as imprima, sendo y impressa com 3 casas decimais e z com 4.
7. A fim de observar como funciona a formatação, edite as seguintes linhas de código em um programa e observe o que acontece em cada printf:
    ~~~c
    printf(“Os alunos são %d.\n”, 350);
    printf(“Os alunos são %2d.\n”, 350);
    printf(“Os alunos são %4d.\n”, 350);
    printf(“Os alunos são %6d.\n”, 350);
    printf(“Os alunos são %02d.\n”, 350);
    printf(“Os alunos são %04d.\n”, 350);
    printf(“Os alunos são %06d.\n”, 350);
    printf(“Os alunos são %10.02d.\n”, 350);
    printf(“Os alunos são %10.04d.\n”, 350);
    printf(“Os alunos são %10.06d.\n”, 350);
    ~~~
8. Observe as instruções abaixo:
    * a) `printf(“ab%dcd”, 27)`; imprime o texto substituindo o `%d` pelo número contido após a vírgula, ou seja, imprime `ab27cd`
    * b) `printf(“xy%3dwz”, 65)`; faz o mesmo com o número ocupando 3 posições da linha, alinhado no lado direito, ou seja, imprime `xy 65wz`
    * c) `printf(“*a%-4d*a”, 58)`; faz o mesmo com o número ocupando 4 posições da linha, alinhado no lado esquerdo, ou seja, imprime `*a58  *a` Com base nos exemplos anteriores, faça um programa que reproduza a figura abaixo, sem utilizar espaço em branco no printf:
    ```c
    *1111 1111*
    *111   111*
    *11     11*
    *1       1*
    *11     11*
    *111   111*
    *1111 1111*
    ```
1. Declare 2 constantes (PI e DOLAR) e atribua valores a elas. As declarações devem ser feitas de modos distintos. A seguir, imprima as constantes.
2.  Declare uma constante denominada NUM, cujo valor deve ser 5. A seguir, imprima o valor do sucessor da constante e do antecessor da mesma, utilizando os operadores de soma e subtração.