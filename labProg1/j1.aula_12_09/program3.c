#include <stdio.h>

void func200() {
    int n, nPares = 0, nImpares = 0, somatorio = 0;
    float media;

    for(int i = 0; i < 200; i++) {
        scanf("%d", &n);
        if(n % 2 == 0) {
            nPares++;
        } else {
            nImpares++;
        }
        somatorio += n;
    }
    media = (float) somatorio / 200;
    printf("\nMedia: %.2f", media);
    printf("\nQuantidade de numeros pares: %d", nPares);
    printf("\nQuantidade de numeros impares: %d", nImpares);
    printf("\nSomatorio: %d", somatorio);
}

int main()
{
    func200();
    return 0;
}
