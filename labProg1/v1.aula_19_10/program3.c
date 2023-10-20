#include <stdio.h>

void invertNum (int *x) {
    int aux = 0;
    while (*x > 0) {
        aux = aux * 10 + *x % 10;
        *x /= 10;
    }
    *x = aux;
}

int main(int argc, char const *argv[])
{
    int x;

    printf("Digite um numero inteiro: ");
    scanf("%d", &x);

    invertNum(&x);

    printf("Numero invertido: %d\n", x);
    return 0;
}
