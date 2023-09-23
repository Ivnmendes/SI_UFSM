#include <stdio.h>

int main(int argc, char const *argv[]) {
    int num, soma = 0, cont = 0;

    do {
        scanf("%d", &num);

        if(num % 2 == 0 && num != 0) {
            soma += num;
            cont++;
        }
    } while (num != 0);

    printf("%.2f\n", soma/(float)cont);
    return 0;
}
