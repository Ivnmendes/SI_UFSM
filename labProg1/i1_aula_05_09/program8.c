#include <stdio.h>

float calcJuros(float valor, int prazo) {
    float resultado;

    switch (prazo) {
        case 0: case 1: case 2: case 3:
            resultado = valor;
            break;
        case 4: case 5: case 6: case 7:
            resultado = valor + (valor * prazo * 0.5 / 100);
            break;
        case 8: case 9: case 10: case 11: case 12:
            resultado = valor + (valor * prazo * 1.5 / 100);
            break;
        case 13: case 14: case 15: case 16: case 17: case 18: case 19: case 20:
            resultado = valor + (valor * prazo * 3 / 100);
            break;
        default:
            printf("Prazo Invalido!");
            return 0;
            break;
    }

    return resultado;
}

int main(int argc, char const *argv[]) {
    float vCompra;
    int prazo;
    printf("Insira o valor da compra e o prazo de pagamento: ");
    scanf("%f", &vCompra);
    scanf("%d", &prazo);

    printf("\n O valor final sera de R$%.2f", calcJuros(vCompra, prazo));

    return 0;
}
