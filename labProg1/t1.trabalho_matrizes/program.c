#include <stdio.h>

int obterMediana (int vet[], int tam) {
    int mediana;
    if (tam % 2 == 0) {
        mediana = (vet[tam / 2] + vet[(tam / 2) - 1]) / 2;
    } else {
        mediana = vet[tam / 2];
    }

    printf("Mediana: %d\n", mediana);
    return mediana;
}

void imprimirVetor (int vet[], int tam) {
    printf("\n[");
    for (int i = 0; i < tam; i++) {
        printf("%d ", vet[i]);
    }
    printf("]\n");
}

void ordenarVetor (int vet[], int tam) {
    int aux;
    for (int i = 0; i < tam; i++) {
        for (int j = i; j < tam; j++) {
            if (vet[i] > vet[j]) {
                aux = vet[i];
                vet[i] = vet[j];
                vet[j] = aux;
            }
        }
    }

    // Imprime o vetor ordenado
    imprimirVetor(vet, tam);
}

int main()
{
    int i, j;
    printf("Insira os valores de i e j (devem ser maiores que 0 e menores ou iguais a 100)");
    scanf("%d", &i);  
    while (i <= 0 || i > 100)
    {
        printf("Insira um valor válido para i");
        scanf("%d", &i);
    }
    scanf("%d", &j);
    while (j <= 0 || j > 100)
    {
        printf("Insira um valor válido para j");
        scanf("%d", &j);
    }

    int matriz[i][j], matrizMed[i][j];

    // Le a matriz
    printf("Insira os valores da matriz: ");
    for (int k = 0; k < i; k++)
    {
        for (int l = 0; l < j; l++)
        {
            scanf("%d", &matriz[k][l]);
        }
    }

    // Imprime a matriz
    printf("\n");
    for (int k = 0; k < i; k++) {
        for (int l = 0; l < j; l++) {
            printf("%d ", matriz[k][l]);
        }
        printf("\n");
    }

    for (int k = 0; k < i; k++) {
        for (int l = 0; l < j; l++) {
            printf("\n i=%d j=%d\n", k, l);
            if (k == 0 && l == 0) {
                int vetAux[4], cont = 0, x = k;

                while (cont < 4) {
                    for (int z = l; z < l + 2; z++)
                    {
                        vetAux[cont] = matriz[x][z];
                        cont++;
                    }
                    if (x < k + 1) {
                       x++;
                    }
                }

                imprimirVetor(vetAux, 4);
                ordenarVetor(vetAux, 4);
                matrizMed[k][l] = obterMediana(vetAux, 4);
            } else if (k == 0 && l == j - 1) {
                int vetAux[4], cont = 0, x = k;
                while (cont < 4) {
                    for (int z = l; z > l - 2; z--)
                    {
                        vetAux[cont] = matriz[x][z];
                        cont++;
                    }
                    if (x < k + 1) {
                       x++;
                    }
                }

                imprimirVetor(vetAux, 4);
                ordenarVetor(vetAux, 4);
                matrizMed[k][l] = obterMediana(vetAux, 4);
            } else if (k == i - 1 && l == 0) {
                int vetAux[4], cont = 0, x = k;

                while (cont < 4) {
                    for (int z = l; z < l + 2; z++)
                    {
                        vetAux[cont] = matriz[x][z];
                        cont++;
                    }
                    if (x > k - 1) {
                       x--;
                    }
                }

                imprimirVetor(vetAux, 4);
                ordenarVetor(vetAux, 4);
                matrizMed[k][l] = obterMediana(vetAux, 4);
            } else if (k == i - 1 && l == j - 1) {
                int vetAux[4], cont = 0, x = k;

                while (cont < 4) {
                    for (int z = l; z > l - 2; z--)
                    {
                        vetAux[cont] = matriz[x][z];
                        cont++;
                    }
                    if (x > k - 1) {
                       x--;
                    }
                }

                imprimirVetor(vetAux, 4);
                ordenarVetor(vetAux, 4);
                matrizMed[k][l] = obterMediana(vetAux, 4);
            } else if (k == 0 ) {
                int vetAux[6], cont = 0, x = k;
                while (cont < 6) {
                    for (int z = l - 1 ; z < l + 2; z++)
                    {
                        vetAux[cont] = matriz[x][z];
                        cont++;
                    }
                    if (x < k + 1) {
                       x++;
                    }
                }

                imprimirVetor(vetAux, 6);
                ordenarVetor(vetAux, 6);
                matrizMed[k][l] = obterMediana(vetAux, 6);
            
            } else if (k == i - 1) {
                int vetAux[6], cont = 0, x = k;
                while (cont < 6) {
                    for (int z = l - 1 ; z < l + 2; z++)
                    {
                        vetAux[cont] = matriz[x][z];
                        cont++;
                    }
                    if (x > k - 1) {
                       x--;
                    }
                }

                imprimirVetor(vetAux, 6);
                ordenarVetor(vetAux, 6);
                matrizMed[k][l] = obterMediana(vetAux, 6);
            } else if (l == 0) {
                int vetAux[6], x = l, cont = 0;
                while (cont < 6) {
                    for (int z = k - 1; z < k + 2; z++)
                    {
                        vetAux[cont] = matriz[z][x];
                        cont++;
                    }
                    if (x < l + 1) {
                       x++;
                    }
                }

                imprimirVetor(vetAux, 6);
                ordenarVetor(vetAux, 6);
                matrizMed[k][l] = obterMediana(vetAux, 6);
            
            } else if (l == j - 1) {
                int vetAux[6], x = l, cont = 0;
                while (cont < 6) {
                    for (int z = k - 1; z < k + 2; z++)
                    {
                        vetAux[cont] = matriz[z][x];
                        cont++;
                    }
                    if (x > l - 1) {
                       x--;
                    }
                }

                imprimirVetor(vetAux, 6);
                ordenarVetor(vetAux, 6);
                matrizMed[k][l] = obterMediana(vetAux, 6);
            } else {
                int vetAux[9], cont = 0, x = k - 1;
                while (cont < 9) {
                    for (int z = l - 1; z < l + 2; z++)
                    {
                        vetAux[cont] = matriz[x][z];
                        cont++;
                    }
                    if (x < l + 1) {
                       x++;
                    }
                }

                imprimirVetor(vetAux, 9);
                ordenarVetor(vetAux, 9);
                matrizMed[k][l] = obterMediana(vetAux, 9);
            }
            
        }
    }

    printf("\n");
    // Exibe a matrizMed
    printf("matrizMed:\n");
    for (int k = 0; k < i; k++) {
        for (int l = 0; l < j; l++) {
            printf("%d ", matrizMed[k][l]);
        }
        printf("\n");
    }
    return 0;
}
