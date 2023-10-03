#include <stdio.h>

#define TAM 5

void trocarLinhas(int mat[TAM][TAM], int linha1, int linha2) {
    int matTrocada[TAM][TAM];
    // Troca as linhas
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if(i == linha1) {
                matTrocada[i][j] = mat[linha2][j];
            } else if (i == linha2) {
                matTrocada[i][j] = mat[linha1][j];
            } else {
                matTrocada[i][j] = mat[i][j];
            }
        }
    }

    // Imprime a matriz trocada
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", matTrocada[i][j]);
        }
        printf("\n");
    }
}

void trocarColunas(int mat[TAM][TAM], int coluna1, int coluna2) {
    int matTrocada[TAM][TAM];
    // Troca as colunas
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if(j == coluna1) {
                matTrocada[i][j] = mat[i][coluna2];
            } else if (j == coluna2) {
                matTrocada[i][j] = mat[i][coluna1];
            } else {
                matTrocada[i][j] = mat[i][j];
            }
        }
    }

    // Imprime a matriz trocada
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", matTrocada[i][j]);
        }
        printf("\n");
    }
}

void trocarDiagonais(int mat[TAM][TAM]) {
    int matTrocada[TAM][TAM];
    // Troca as diagonais
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if(i == j) {
                matTrocada[i][j] = mat[i][TAM - 1 - j];
            } else if (i + j == TAM - 1) {
                matTrocada[i][j] = mat[i][TAM - 1 - j];
            } else {
                matTrocada[i][j] = mat[i][j];
            }
        }
    }

    // Imprime a matriz trocada
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", matTrocada[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char const *argv[])
{
    int mat[TAM][TAM];

    // Le os valores da matriz
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            scanf("%d", &mat[i][j]);
        }
    }

    printf("Matriz trocando a segunda linha pela quinta:\n\n");
    trocarLinhas(mat, 1, 4);

    printf("\nMatriz trocando a terceira coluna pela quinta:\n\n");
    trocarColunas(mat, 2, 4);

    printf("\nMatriz trocando a diagonal principal pela secundaria:\n\n");
    trocarDiagonais(mat);
    
    return 0;
}
