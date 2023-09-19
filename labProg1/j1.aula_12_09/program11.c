#include <stdio.h>

int main(int argc, char const *argv[])
{
    int soma = 0, min, max;
    scanf("%d",&min);
    scanf("%d",&max);

    for(int i = min; i < max; i++) {
        if(i% 2 != 0) {
            printf("%d ", i);
            soma += i;
        }
    }
    printf("\nSoma = %d", soma);
    return 0;
}
