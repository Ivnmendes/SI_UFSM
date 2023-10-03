#include <stdio.h>

#define TAMLINHA 2
#define TAMCOLUNA 3

int main(int argc, char const *argv[])
{
    int mat[TAMLINHA][TAMCOLUNA];

    // Le os valores da matriz
    for (int i = 0; i < TAMLINHA; i++) {
        for (int j = 0; j < TAMCOLUNA; j++) {
            scanf("%d", &mat[i][j]);
        }
    }

    // Exibe a matriz transposta
    for (int i = 0; i < TAMCOLUNA; i++) {
        for (int j = 0; j < TAMLINHA; j++) {
            printf("%d ", mat[j][i]);
        }
        printf("\n");
    }
    return 0;
}
