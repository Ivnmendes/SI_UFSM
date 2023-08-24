#include <stdio.h>

int main(int argc, char const *argv[]) {
    float a, b;
    char operador;

    printf("Insira um numero: ");
    scanf("%f", &a);
    printf("Insira um numero: ");
    scanf("%f", &b);
    printf("Insira o operador (+,-,*,/): ");
    scanf(" %c", &operador);

    if (operador == '*') {
        printf("%.1f %c %.1f = %.1f",a,operador,b,a*b);
    } else if (operador == '+') {
        printf("%.1f %c %.1f = %.1f",a,operador,b,a+b);
    } else if (operador == '-') {
        printf("%.1f %c %.1f = %.1f",a,operador,b,a-b);
    } else if (operador == '/') {
        if(b == 0) {
            printf("Nao e possivel dividir por zero\n");
        } else {
            printf("%.1f %c %.1f = %.1f",a,operador,b,a-b);
        }
    } else {
        printf("Operador invalido\n");
    }
    return 0;
}
