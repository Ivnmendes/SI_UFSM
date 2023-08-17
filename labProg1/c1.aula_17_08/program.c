#include <stdio.h>

int main() {
    float nota1,nota2;
    int peso1,peso2;
    printf("Insira a nota 1: ");
    scanf("%f", &nota1);
    printf("Insira a nota 2: ");
    scanf("%f", &nota2);
    printf("Insira o peso 1: ");
    scanf("%d", &peso1);
    printf("Insira o peso 2: ");
    scanf("%d", &peso2);

    float media = (nota1 * peso1 + nota2 * peso2) / (peso1 + peso2);
    printf("Media: %.1f\n", media);
    return 0;
}
