#include <stdio.h>

void calcQuoAndRest(int x, int y) {
    int result = x, cont = 0, resto, quociente;

    while(result - y >= 0) {
        if(y * cont < x) {
            result -= y;

            cont++;
        } else {
            break;
        }

    }

    resto = result;
    quociente = cont;

    printf("Resto: %d\n", result);
    printf("Quociente: %d\n", cont);
}

int main(int argc, char const *argv[]) {
    int x, y;

    scanf("%d", &x);
    scanf("%d", &y);

    calcQuoAndRest(x, y);
    return 0;
}
