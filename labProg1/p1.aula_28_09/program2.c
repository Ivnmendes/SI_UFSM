#include <stdio.h>

#define TAM 5

int main(int argc, char const *argv[]) {
    float vet[TAM];
    printf("Insira os valores do vetor: ");
    for(int i = 0; i < TAM; i++) {
        scanf("%f", &vet[i]);
    }
    printf("Vetor [");
    for(int i = 0; i < TAM; i++) {
        printf("%.2f ", vet[i]);
    }
    printf("]\n");
    for (int j = 0; j < TAM; j++) {
        if(vet[j] == 0) {
            vet[j] = -99;
        }
    }
    printf("\nVetor [");
    for(int j = 0; j < TAM; j++) {
        printf("%.2f ", vet[j]);
    }
    printf("]\n");
    return 0;
}
