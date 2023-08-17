#include <stdio.h>

int main(int argc, char const *argv[]) {
    int x,y;
    printf("Insira o valor de x: ");
    scanf("%d", &x);
    printf("Insira o valor de y: ");
    scanf("%d", &y);

    printf("%d\n%d", ++x,--y);
    return 0;
}
