#include <stdio.h>

void gastoCombustivel() {
    int kmRodados;
    float vGasto;
    printf("Insira os quilometros rodados (0..900): ");
    scanf("%d", &kmRodados);

    if(kmRodados >= 0 && kmRodados <= 900) {
        if(kmRodados / 10 >= 45) {
            vGasto = 2.3 * kmRodados/10;
        } else {
            vGasto = 2.5 *kmRodados/10;
        }
        printf("O valor gasto foi de R$%.2f", vGasto);
    } else {
        printf("Valor invalido");
    }
}

int main(int argc, char const *argv[]) {
    gastoCombustivel();
    return 0;
}
