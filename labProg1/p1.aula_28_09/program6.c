#include <stdio.h>

#define TAM 10

int main(int argc, char const *argv[]) {
    int cont = 0, vetA[TAM], vetB[TAM], vetC[TAM * 2], aux;

    printf("Digite os valores do vetor A: ");
    for (int i = 0; i < TAM; i++) {
        scanf("%d", &vetA[i]);
    }
    printf("Digite os valores do vetor B: ");
    for (int i = 0; i < TAM; i++) {
        scanf("%d", &vetB[i]);
    }

    printf("Vetor A: [");
    for (int i = 0; i < TAM; i++) {
        printf("%d ", vetA[i]);
    }
    printf("]\n");
    printf("Vetor B: [");
    for (int i = 0; i < TAM; i++) {
        printf("%d ", vetB[i]);
    }
    printf("]\n");

    // Atribui ambos os vetores ao vetor C
    for (int j = 0; j < TAM * 2; j++) {
        vetC[j] = vetA[j];
        if(j >= TAM) {
            vetC[j] = vetB[cont];
            cont++;
        }
    }

    // Ordena o vetor C em ordem decrescente
    for(int j = 0; j < TAM * 2- 1; j++) {
        for(int h = j; h < TAM * 2; h++) {
            if (vetC[j] < vetC[h]) {
                aux = vetC[j];
                vetC[j] = vetC[h];
                vetC[h] = aux;
            }
        }
    }

    printf("Vetor C: [");
    for (int z = 0; z < TAM * 2; z++) {
        printf("%d ", vetC[z]);
    }
    printf("]\n");
    return 0;
}
