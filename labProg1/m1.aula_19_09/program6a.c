#include <stdio.h>

int main(int argc, char const *argv[]) {
    int num, soma = 0, cont = 0;
    float media;

    scanf("%d", &num);
    while (num != 0) {
        if(num % 2 == 0) {
            soma += num;
            cont++;
        }

        scanf("%d", &num);
    }

    media = (float) soma/cont;

    printf("Media: %.2f\n", media);
    return 0;
}
