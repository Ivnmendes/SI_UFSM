#include <stdio.h>

int main(int argc, char const *argv[])
{
    int n, j, m;
    scanf("%d", &n);
    scanf("%d", &j);
    scanf("%d", &m);

    if(n > 0 && j > 0 && m > 0) {
        for(int i = 1; n > 0; i++) {
            if((i % j) == (m % j)) {
                printf("%d e congruente modulo %d a %d\n", i,j,m);
                n--;
            }
        }
    } else {
        printf("Os numeros devem ser positivos");
    }
    return 0;
}
