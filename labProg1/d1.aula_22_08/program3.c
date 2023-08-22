#include <stdio.h>

int main() {
    float base, altura;
    printf("Insira a base do triangulo: ");
    scanf("%f", &base);
    printf("Insira a altura do triangulo: ");
    scanf("%f", &altura);

    printf("A altura do triangulo e: %.2f", (float) base * altura / 2);

    return 0;
}