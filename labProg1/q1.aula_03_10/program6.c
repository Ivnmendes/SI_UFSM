#include <stdio.h>

#define TAM 3

int main(int argc, char const *argv[])
{
    int mat[TAM][TAM], vet[TAM];

    // Le os valores da matriz
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            scanf("%d", &mat[i][j]);
        }
    }

    // Le os valores do vetor
    for (int i = 0; i < TAM; i++) {
        scanf("%d", &vet[i]);
    }

    // Multiplica a matriz pelo vetor
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", mat[i][j] * vet[j]);
        }
        printf("\n");
    }
    return 0;
}
