#include <stdio.h>

int main(int argc, char const *argv[]) {
    int num, tot = 1, cont = 0;

    do {
        scanf("%d", &num);

        if(num >= 0) {
            tot *= num;
        }
    } while(num >= 0);

    printf("Produto: %d", tot);
    return 0;
}
