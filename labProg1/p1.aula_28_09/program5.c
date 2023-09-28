#include <stdio.h>

#define TAM 10

int main(int argc, char const *argv[]) {
    int cont = 0, aux, vet[TAM];
    printf("Insira os valores: ");
    for (int i = 0; i < TAM; i++) {
        scanf("%d", &vet[i]);
    }

    printf("Vetor: [");
    for (int i = 0; i < TAM; i++) {
        printf("%d ", vet[i]);
    }
    printf("]\n");

    for (int j = TAM - 1; j > 0; j--) {
        aux = vet[j];
        vet[j] = vet[cont];
        vet[cont] = aux;
        cont++;
    }

    printf("Vetor trocado: [");
    for (int i = 0; i < TAM; i++) {
        printf("%d ", vet[i]);
    }
    printf("]\n");
    return 0;
}
