#include <stdio.h>

#define TAM 10

int main(int argc, char const *argv[]) {
    int num, cont = 0, vet[TAM];
    printf("Insira os %d valores do vetor: ", TAM);
    for(int i = 0; i < TAM; i++) {
        scanf("%d", &vet[i]);
    }

    printf("Insira o numero a ser buscado: ");
    scanf("%d", &num);
    for(int n = 0; n < TAM; n++) {
        if(vet[n] == num) {
            cont++;
        }
    }

    printf("Numero %d encontrado %d vezes!\n", num, cont);
    return 0;
}
