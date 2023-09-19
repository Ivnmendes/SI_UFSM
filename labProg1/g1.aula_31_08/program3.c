#include <stdio.h>

int main(int argc, char const *argv[]) {
    int op;

    scanf("%d", &op);

    switch (op) {
        case 1:
            printf("Alimento nao perecivel\n");
            break;
        case 2: case 3: case 4:
            printf("Alimento perecivel\n");
            break;
        case 5: case 6:
            printf("Higiene pessoal\n");
            break;
        case 7:
            printf("Utensilios domesticos\n");
            break;
        case 8: case 9: case 10: case 11: case 12:
            printf("Limpeza\n");
            break;
        default:
            printf("Codigo invalido\n");
            break;
    }
    return 0;
}
