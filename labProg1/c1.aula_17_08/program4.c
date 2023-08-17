#include <stdio.h>

int main(int argc, char const *argv[]) {
    printf("Insira o preço base: ");
    float pBase;
    scanf("%f", &pBase);

    float desconto = pBase - (pBase * 0.1);
    float aumento = pBase + (pBase * 0.2);

    printf("\nPreço base: R$%.2f\nCom desconto: R$%.2f\n", pBase, desconto);
    printf("\nPreço base: R$%.2f\nCom aumento: R$%.2f",pBase,aumento);
    return 0;
}
