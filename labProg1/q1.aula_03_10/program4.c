#include <stdio.h>

#define TAM 2
int main(int argc, char const *argv[])
{
    int mat[TAM][TAM], determinante;
    int somaPrincipal = 1, somaSecundaria = 1;
    // Le os valores da matriz
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            scanf("%d", &mat[i][j]);
        }
    }

    // Calcula o produto da diagonal principal e da diagonal secundaria
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if(i == j && i + j != TAM - 1){
                somaPrincipal *= mat[i][j];
            } else if (i + j == TAM - 1) {
                somaSecundaria *= mat[i][j];
            }
        }
    }

    determinante = somaPrincipal - somaSecundaria;
    printf("Determinante: %d\n", determinante);
    return 0;
}
