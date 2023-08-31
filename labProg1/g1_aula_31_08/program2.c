#include <stdio.h>

int main(int argc, char const *argv[]) {
    float x, y;
    char op;
    scanf("%f", &x);
    scanf(" %c", &op);
    scanf("%f", &y);

    switch (op) {
        case '+':
            printf("%.1f %c %.1f = %.2f\n", x,op,y,x+y);
            break;
        case '-':
            printf("%.1f %c %.1f = %.2f\n", x,op,y,x-y);
            break;
        case '*':
            printf("%.1f %c %.1f = %.2f\n", x,op,y,x*y);
            break;
        case '/':
            if(y == 0) {
                printf("O denominador deve ser maior que zero\n");
            } else {
                printf("%.1f %c %.1f = %.2f\n", x,op,y,x/y);
            }
            break;
        default:
            printf("Operador invalido!\n");
            break;
    }
    return 0;
}
