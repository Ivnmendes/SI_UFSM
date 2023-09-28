#include <stdio.h>
#include <limits.h>

#define TAM 10

int main(int argc, char const *argv[]) {
    int menor = INT_MAX, posMenor, vet[TAM];
    printf("Insira os valores do vetor: ");
    for (int i = 0; i < TAM; i++) {
        scanf("%d", &vet[i]);
    }
    for (int i = 0; i < TAM; i++) {
        if(vet[i] < menor) {
            menor = vet[i];
            posMenor = i;
        }
    }

    printf("O menor valor e %d na posicao %d\n", menor, posMenor);
    return 0;
}
