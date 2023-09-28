#include <stdio.h>

#define TAM 50

int main(int argc, char const *argv[]) {
    int num, vet[TAM], contPares = 0, contImpares = 0;
    int x = 0, y = 0;
    printf("Insira os valores a serem lidos: ");
    for (int i = 0; i < TAM; i++) {
        scanf("%d", &vet[i]);
        if(vet[i] % 2 == 0) {
            contPares++;
        } else {
            contImpares++;
        }
    }

    int vetPar[contPares], vetImpar[contImpares];

    for (int i = 0; i < TAM; i++) {
        if(vet[i] % 2 == 0) {
            vetPar[x] = vet[i];
            x++;
        } else {
            vetImpar[y] = vet[i];
            y++;
        }
    }

    printf("Vet par [");
    for (int j = 0; j < contPares; j++) {
        printf("%d ", vetPar[j]);
    }
    printf("]\n");

    printf("Vet impar [");
    for (int j = 0; j < contImpares; j++) {
        printf("%d ", vetImpar[j]);
    }
    printf("]\n");
    return 0;
}
