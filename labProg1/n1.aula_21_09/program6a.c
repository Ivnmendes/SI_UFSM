#include <stdio.h>

int main(int argc, char const *argv[]) {
    int num, soma = 0, cont = 0;

    scanf("%d", &num);
    while (num != 0) {
        if(num % 2 == 0) {
            soma += num;
            cont++;
        }

        scanf("%d", &num);
    }

    printf("%.2f\n", soma/(float)cont);
    return 0;
}
