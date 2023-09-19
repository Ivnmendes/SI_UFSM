#include <stdio.h>

int main(int argc, char const *argv[])
{
    int n, soma =0;

    for(int i = 0; i < 20; i++) {
        scanf("%d", &n);
        if(n * n < 225) {
            soma += n;
        }
    }

    printf("Soma: %d", soma);
    return 0;
}
