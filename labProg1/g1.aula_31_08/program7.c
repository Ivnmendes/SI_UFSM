#include <stdio.h>
#include <ctype.h>

int main(int argc, char const *argv[]) {
    char op;
    int altura;

    scanf(" %c", &op);
    scanf("%d", &altura);

    switch (tolower(op)) {
        case 'm':
            printf("Peso ideal: %.2f\n", (altura - 100) * 0.9);
            break;
        case 'f':
            printf("Peso ideal: %.2f\n", (altura - 100) * 0.85);
            break;
        default:
            printf("Opcao invalida!\n");
            break;
    }
    return 0;
}
