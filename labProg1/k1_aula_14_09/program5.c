#include <stdio.h>

int checkQuadradoPerfeito(int num) {
    int soma = 0, cont = 0, i = 1;

    while(soma < num) {
        soma += i;
        i += 2;
        cont++;
    }

    if(soma == num) {
        return cont;
    } else {
        return -1;
    }

}

int main(int argc, char const *argv[]) {
    int n, quadradoPerfeito;
    scanf("%d", &n);

    quadradoPerfeito = checkQuadradoPerfeito(n);

    if(quadradoPerfeito == -1) {
        printf("%d nao tem quadrado perfeito\n", n);
    } else {
        printf("O quadrado perfeito de %d e: %d\n", n, quadradoPerfeito);
    }
    return 0;
}
