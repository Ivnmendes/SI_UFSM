#include <stdio.h>

int main(int argc, char const *argv[]) {
    float pesoA, pesoB, pesoC, pesoD;

    printf("Insira o peso de a: ");
    scanf("%f", &pesoA);
    printf("Insira o peso de b: ");
    scanf("%f", &pesoB);
    printf("Insira o peso de c: ");
    scanf("%f", &pesoC);
    printf("Insira o peso de d: ");
    scanf("%f", &pesoD);

    if(pesoA == pesoB + pesoC + pesoD && pesoD == pesoB + pesoC && pesoB == pesoC)
        printf("Esta equilibrado");
    else
        printf("Nao esta equilibrado");
    return 0;
}
