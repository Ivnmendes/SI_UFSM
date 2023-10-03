#include <stdio.h>

#define TAM 4

int main(int argc, char const *argv[])
{
    int mat[TAM][TAM], mat2[TAM][TAM], mat3[TAM][TAM];

    // Le os valores da matriz 1
    printf("Primeira matriz: \n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            scanf("%d", &mat[i][j]);
        }
    }

    // Le os valores da matriz 2
    printf("Segunda matriz: \n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            scanf("%d", &mat2[i][j]);
        }
    }

    // Constroi uma matriz a partir dos maiores valores da cada posicao entre a matriz 1 e a matriz 2
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            mat3[i][j] = mat[i][j] > mat2[i][j] ? mat[i][j] : mat2[i][j];
        }
    }

    // Imprime a matriz 3
    printf("Matriz 3: \n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", mat3[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
