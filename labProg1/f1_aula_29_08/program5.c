#include <stdio.h>

int main(int argc, char const *argv[]) {
    char op;
    int a, b, maiorNumero, result = 0;

    printf("Insira o maior numero que o computador pode registrar: ");
    scanf("%d", &maiorNumero);
    scanf("%d", &a);
    scanf(" %c", &op);
    scanf("%d", &b);

    switch (op){
        case '+':
            result = a + b;
            if(result > maiorNumero)
                printf("Overflow");
            else
                printf("Ok");
            break;
        case '*':
            result = a * b;
            if(result > maiorNumero)
                printf("Overflow");
            else
                printf("Ok");
            break;
        default:
            printf("Operacao invalida");
            break;
    }

    return 0;
}
