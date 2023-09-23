#include <stdio.h>

void imprimirTabuada(int x, int y) {
    //Calcula o tamanho da tabela com base no numero de colunas * o numero de caracteres de cada coluna
    int larguraTabela = (y - x + 1) * 5;
    //Imprime a primeira, a segunda e a terceira linha da tabela
    for (int i = 0; i < larguraTabela + 5; i++) {
        printf("-");
    }
    printf("\n");
    printf("|%4s", "|");
    for (int i = x; i <= y; i++) {
        printf("%4d|", i);
    }
    printf("\n");
    for (int i = 0; i < larguraTabela + 5; i++) {
        printf("-");
    }
    printf("\n");

    for (int i = x; i <= y; i++) {
        printf("|%2d%2s", i, "|");
        for(int j = x; j <= y; j++) {
            printf("%4d|", i * j);
        }
        printf("\n");
    }
    for (int i = 0; i < larguraTabela + 5; i++) {
        printf("-");
    }
}

int main(int argc, char const *argv[]) {
    int x, y;

    printf("Digite os valores para x e y: ");
    scanf("%d", &x);
    scanf("%d", &y);

    //Checa se os valores inseridos são válidos (a tabela só funciona com números de até 5 digitos)
    while (x > y || y * y >= 10000) {
        printf("Valores invalidos!\n");
        printf("Digite os valores para x e y: ");
        scanf("%d", &x);
        scanf("%d", &y);
    }
    printf("\nTabuada de multiplicacao!\n");
    imprimirTabuada(x,y);
    return 0;
}
