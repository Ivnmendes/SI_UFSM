#include <stdio.h>

#define TAM 100

int main(int argc, char const *argv[])
{
    int cont = 0, vetA[TAM];
    
    // Le os valores do vetor A
    printf("Digite os valores do vetor A: ");
    for (int i = 0; i < TAM; i++)
    {
        scanf("%d", &vetA[i]);
    }

    // Verifica quantos maiores que zero existem no vetor A
    for (int i = 0; i < TAM; i++)
    {
        if (vetA[i] > 0) {
            cont++;
        }
    }

    int vetB[cont];
    
    // Atribui os valores nao nulos e nao negativos do vetor A para o vetor B
    for (int i = 0, j = 0; i < TAM; i++)
    {
        if (vetA[i] > 0) {
            vetB[j] = vetA[i];
            j++;
        }
    }

    // Imprime o vetor B
    printf("Vetor B: ");
    for (int i = 0; i < cont; i++)
    {
        printf("%d ", vetB[i]);
    }
    return 0;
}
