#include <stdio.h>
#include <ctype.h>

int main(int argc, char const *argv[]) {
    float salario;
    char op;

    scanf("%f", &salario);
    scanf(" %c", &op);

    switch (tolower(op)) {
        case 'a':
        printf("Salario reajustado: R$%.2f\n", salario + (salario * 0.09));
            break;
        case 'b':
            printf("Salario reajustado: R$%.2f\n", salario + (salario * 0.13));
            break;
        case 'c':
            printf("Salario reajustado: R$%.2f\n", salario + (salario * 0.17));
            break;
        default:
            printf("Opcao invalida!\n");
            break;
    }
    return 0;
}
