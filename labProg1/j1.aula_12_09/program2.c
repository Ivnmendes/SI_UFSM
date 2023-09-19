#include <stdio.h>

int main(int argc, char const *argv[])
{
    int soma = 0;
    for(int i = 100; i <= 200; i++) {
        if(i % 13 != 0) {
            soma += i;
        }
    }

    printf("%d", soma);
    return 0;
}
