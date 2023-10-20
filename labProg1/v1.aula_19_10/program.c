#include <stdio.h>

void quantDiv (int *x) {
    int cont = 2;
    for (int i = 2; i <= *x / 2; i++)
    {
        if (*x % i == 0) {
            cont++;
        }
    }

    *x = cont;
}

int main(int argc, char const *argv[])
{
    int m, n;

    scanf("%d", &m);
    quantDiv(&m);

    printf("Numero de divisores: %d\n", m);

    scanf("%d", &n);
    quantDiv(&n);

    printf("Numero de divisores: %d\n", n);
    return 0;
}
