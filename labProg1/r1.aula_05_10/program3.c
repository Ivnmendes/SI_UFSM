#include <stdio.h>
#include <limits.h>

#define TAM 30

int main(int argc, char const *argv[])
{
    int vet[TAM], maiorValor = INT_MIN, menorValor = INT_MAX;
    
    // Le os valores do vetor
    printf("Digite os valores do vetor: ");
    for (int i = 0; i < TAM; i++)
    {
        scanf("%d", &vet[i]);
    }

    // Verifica o maior e o menor valor do vetor
    for (int i = 0; i < TAM; i++)
    {
        if (vet[i] < menorValor) {
            menorValor = vet[i];
        }
        if (vet[i] > maiorValor) {
            maiorValor = vet[i];
        }
    }

    // Exibe a diferença entre o maior e o menor valor
    printf("A diferenca entre o maior e o menor valor e %d\n", maiorValor - menorValor);
    return 0;
}
