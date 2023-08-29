#include <stdio.h>

int main(int argc, char const *argv[]) {
    int consumo;
    float aux, vConta = 0, tFixa = 7.;

    printf("Insira o consumo da residencia (em metros cubicos): ");
    scanf("%d", &consumo);

    if(consumo > 100) {
        aux = consumo - 100;
        vConta += aux * 5.;
        consumo -= aux;
    }
    if(consumo > 30) {
        aux = consumo - 30;
        vConta += aux * 2.;
        consumo -= aux;
    }
    if (consumo > 10) {
        aux = consumo - 10;
        vConta += aux * 1.;
        consumo -= aux;
    }
    if(consumo > 0) {
        vConta += 7;
    }

    printf("O valor da conta foi R$%.2f", vConta);

    return 0;
}
