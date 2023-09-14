#include <stdio.h>

char checkTriangular(int num) {
    int x = 1, y = 2, z =3, soma = 0;
    char triangular = 'n';

    while(soma < num) {
        soma = x++ * y++ * z++;
    }

    if(soma == num) {
        triangular = 's';
    }

    return triangular;
}

int main(int argc, char const *argv[]) {
    int num;
    scanf("%d", &num);

    if(checkTriangular(num) == 's') {
        printf("%d e triangular!\n", num);
    } else {
        printf("%d nao e triangular!\n", num);
    }
    return 0;
}
