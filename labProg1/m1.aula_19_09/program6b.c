#include <stdio.h>

int main(int argc, char const *argv[]) {
    int num, soma = 0, cont = 0;
    float media;

    do {
        scanf("%d", &num);

        if(num % 2 == 0 && num != 0) {
            soma += num;
            cont++;
        }
    } while (num != 0);

    media = (float) soma/cont;

    printf("Media: %.2f\n", media);
    return 0;
}
