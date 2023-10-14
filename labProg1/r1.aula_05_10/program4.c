#include <stdio.h>

#define TAM 10

int main(int argc, char const *argv[])
{
    int vet[TAM], contPares = 0;

    // Le os valores do vetor
    printf("Digite os valores do vetor: ");
    for (int i = 0; i < TAM; i++)
    {
        scanf("%d", &vet[i]);
    }

    // Conta a quantidade de numeros pares
    for (int i = 0; i < TAM; i++)
    {
        if (vet[i] % 2 == 0) {
            contPares++;
        }
    }

    // Exibe a quantidade de numeros pares
    printf("A quantidade de numeros pares e %d\n", contPares);
    return 0;
}
