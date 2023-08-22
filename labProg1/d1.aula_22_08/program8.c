#include <stdio.h>

#define PCOMBUSTIVEL 6.99

int main() {
    float mOdometroInicio, mOdometroFim, cGasto, vRecebido, lucro, mConsumo;

    printf("Insira a marcacao do odometro no inicio do dia (em KM): ");
    scanf("%f", &mOdometroInicio);
    printf("Insira a marcacao do odometro no fim do dia (em KM): ");
    scanf("%f", &mOdometroFim);
    printf("Insira o total de combustivel gasto: ");
    scanf("%f", &cGasto);
    printf("Insira o valor recebido por passageiros: ");
    scanf("%f", &vRecebido);

    mConsumo = (mOdometroFim - mOdometroInicio) / cGasto;
    lucro = vRecebido - (cGasto * PCOMBUSTIVEL);

    printf("Lucro: R$%.2f\nMedia de consumo: %.1f Km/l", lucro, mConsumo);
    return 0;
}