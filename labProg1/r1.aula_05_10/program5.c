#include <stdio.h>

#define TAM 20

int main(int argc, char const *argv[])
{
    int var = 10;
    int contRepetidos = 0, vetA[TAM - var], vetB[TAM];

    // Le os valores do vetor A
    printf("Digite os valores do vetor A: ");
    for (int i = 0; i < TAM - var; i++)
    {
        scanf("%d", &vetA[i]);
    }

    // Le os valores do vetor B
    printf("Digite os valores do vetor B: ");
    for (int i = 0; i < TAM; i++)
    {
        scanf("%d", &vetB[i]);
    }

    for (int i = 0; i < TAM - var; i++) 
    {
        for (int j = 0; j < TAM; j++) {
            if (vetA[i] == vetB[j]) {
                contRepetidos++;
                break;
            }
        }
    }

    int vetC[contRepetidos];

    for (int i = 0; i < TAM - var; i++)
    {
        for (int j = 0; j < TAM; j++)
        {
            if (vetA[i] == vetB[j]) {
                vetC[i] = vetA[i];
                break;
            }
        }        
    }
    
    // Exibe os valores do vetor C
    printf("Os valores do vetor C sao: ");
    for (int i = 0; i < contRepetidos; i++)
    {
        printf("%d ", vetC[i]);
    }
    return 0;
}
