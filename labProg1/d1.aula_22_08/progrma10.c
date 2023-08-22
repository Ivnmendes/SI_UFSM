#include <stdio.h>

int main() {
    int qCarros;
    float vDiaria;

    printf("Insira a quantidade de carros que a locadora possui: ");    
    scanf("%d", &qCarros);
    printf("Insira o valor da diaria (em R$): ");
    scanf("%f", &vDiaria);

    printf(
        "Faturamento anual: R$%.2f"
        "\nValor ganho com multas por mes: R$%.2f"
        "\nTotal de carros no fim do mes: %d",
        qCarros * 1/3 * vDiaria, qCarros * 1/10 * (vDiaria * 1/10), qCarros - (int) (qCarros * 0.05 + qCarros * 1/8)
        );
    return 0;
}