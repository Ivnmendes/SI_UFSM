#include <stdio.h>
#include <ctype.h>

int main(int argc, char const *argv[]) {
    int x, y;
    char op;

    scanf("%d", &x);
    scanf("%d", &y);

    printf("\n'A' Calcula e exibe a media aritmetica\n'P'Calcula e exibe a media ponderada (pesos 4 e 6, respectivamente)\n'R'Calcula e exibe o restp inteiro de y por x\nEscolha uma opcao: ");

    scanf(" %c", &op);

    switch (tolower(op)) {
        case 'a':
            printf("%.2f\n", ((double) x + y) / 2);
            break;
        case 'p':
            printf("%.2f\n", (x * 4. + y * 6.) / (4 + 6));
            break;
        case 'r':
            printf("%d\n", x % y);
            break;
        default:
            printf("Opcao invalida\n");
            break;
    }

    return 0;
}
