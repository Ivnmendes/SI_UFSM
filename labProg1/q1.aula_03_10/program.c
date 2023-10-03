#include <stdio.h>

#define TAM 10

int main(int argc, char const *argv[])
{
    int mat[TAM][TAM];
    // Le os valores da matriz
    for (int i = 0; i < TAM; i++){
        for (int j = 0; j < TAM; j++){
            scanf("%d", &mat[i][j]);
        }
    }

    // Exibe a matriz sem a diagonal secundaria
    for (int i = 0; i < TAM; i++){
        for (int j = 0; j < TAM; j++) {
            // Se estiver na diagonal secundaria, exibe dois espacos sinalizando a ausencia do valor
            if (i + j == TAM - 1){
                printf("  ");
            } else {
                printf("%d ", mat[i][j]);
            }
        }
        printf("\n");
    }
    return 0;
}
