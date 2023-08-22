#include <stdio.h>

int main() {
    int moeda1Real, moeda50Centavo, moeda25Centavo, moeda10Centavo, moeda5Centavo, moeda1Centavo;
    float vEconomizado;

    printf("Modas 1 Real: ");
    scanf("%d", &moeda1Real);
    printf("Modas 50 centavos: ");
    scanf("%d", &moeda50Centavo);
    printf("Modas 25 centavos: ");
    scanf("%d", &moeda25Centavo);
    printf("Modas 10 centavos: ");
    scanf("%d", &moeda10Centavo);
    printf("Modas 5 centavos: ");
    scanf("%d", &moeda5Centavo);
    printf("Modas 1 centavo: ");
    scanf("%d", &moeda1Centavo);

    vEconomizado = moeda1Real * 1 + moeda50Centavo * 0.5 + moeda25Centavo * 0.25 + moeda10Centavo * 0.1 + moeda5Centavo * 0.05 + moeda1Centavo * 0.01;

    printf("Valor economizado: R$%.2f", vEconomizado);
    return 0;
}