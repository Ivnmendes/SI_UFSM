#include <stdio.h>

int main(int argc, char const *argv[]) {
    int num;

    scanf("%d", &num);

    if(num == 0) {
        printf("Nulo\n");
    } else if (num > 0) {
        printf("Positivo\n");
    } else {
        printf("Negativo\n");
    }

    return 0;
}
