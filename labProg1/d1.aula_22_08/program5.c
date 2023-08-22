#include <stdio.h>

int main() {
    int a,b, aux;
    printf("Insira um numero: ");
    scanf("%d", &a);
    printf("Insira um numero: ");
    scanf("%d", &b);

    aux = a;
    a = b;
    b = aux;

    printf("a: %d \nb: %d", a,b);

    return 0;
}