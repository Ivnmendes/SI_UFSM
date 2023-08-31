#include <stdio.h>

int main(int argc, char const *argv[]) {
    int op;
    float peso;

    scanf("%f", &peso);
    scanf("%d", &op);

    switch (op) {
        case 1:
            printf("Peso em Mercurio: %.1f\n", peso/10 * 0.37);
            break;
        case 2:
            printf("Peso em Venus: %.1f\n", peso/10 * 0.88);
            break;
        case 3:
            printf("Peso em Marte: %.1f\n", peso/10 * 0.38);
            break;
        case 4:
            printf("Peso em Jupiter: %.1f\n", peso/10 * 2.64);
            break;
        case 5:
            printf("Peso em Saturno: %.1f\n", peso/10 * 1.15);
            break;
        case 6:
            printf("Peso em Urano: %.1f\n", peso/10 * 1.17);
            break;
        default:
            printf("Opcao invalida!");
            break;
    }
    return 0;
}
