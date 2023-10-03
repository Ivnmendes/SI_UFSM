#include <stdio.h>

#define TAM 5

int main(int argc, char const *argv[])
{
    int mat[TAM][TAM], mat2[TAM][TAM];
    
    // Le os valores da matriz
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            scanf("%d", &mat[i][j]);
        }
    }

    // Exibe a matriz
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    // Exive a matriz cuja soma dos indices e par
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if ((i + j) % 2 == 0) {
                printf("%d ", mat[i][j]);
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
    return 0;
}
