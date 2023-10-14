#include <stdio.h>

#define TAM 20

int main(int argc, char const *argv[])
{
    int vet[TAM];

    // Le os valores do vetor
    printf("Digite os valores do vetor: ");
    for (int i = 0; i < TAM; i++)
    {
        scanf("%d", &vet[i]);
    }

    // Imprime o vetor ao contrario
    printf("Vetor ao contrario: ");
    for (int i = TAM - 1; i >= 0; i--)
    {
        printf("%d ", vet[i]);
    }
    return 0;
}
