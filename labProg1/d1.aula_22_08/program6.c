#include <stdio.h>

int main() {
    int a,b;

    printf("Insira um numero: ");
    scanf("%d", &a);
    printf("Insira um numero: ");
    scanf("%d", &b);

    //Trocando o valor de variaveis sem variavel auxiliar - Nao funciona se o valor das variaveis for o limite do tipo int
    a = a + b;
    b = a - b;
    a = a - b;

    printf("a: %d\nb: %d",a,b);
    return 0;
}