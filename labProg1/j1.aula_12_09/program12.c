#include <stdio.h>

int main(int argc, char const *argv[])
{
    int n, maior = 0, menor = 0;
    for(int i = 0; i < 20; i++) {
        scanf("%d", &n);
        if(n > maior) 
            maior = n;
        
        if(n < menor) 
            menor = n;
        
    }
    printf("Maior: %d\nMenor: %d", maior, menor);
    return 0;
}
