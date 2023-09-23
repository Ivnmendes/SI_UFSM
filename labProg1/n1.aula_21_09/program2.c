#include <stdio.h>

int main(int argc, char const *argv[]) {
    int num, menor = 999, soma = 0, somaMaioresQue100 = 0, cont = 0;
    float media;

    do {
        scanf("%d", &num);

        if(num > 100 && num < 1000) {
            if(num < menor) {
                menor = num;
            }

            somaMaioresQue100 += num;
            cont++;
        }

        soma += num;
    } while(num != -1);

    media = (float) soma / cont;

    printf(
    "O menor valor dentre os maiores que 100 e menores que 1000 (nao incluindo 100 e 1000): %d\n"
    "A media dos valores dentre os maiores que 100 e menores que 1000: %.2f\n"
    "A soma dos valores denntre os maiores que 100 e menores que 1000: %d\n"
    "A soma de todos os valores lidos: %d"
    , menor, media, somaMaioresQue100, soma);
    return 0;
}
