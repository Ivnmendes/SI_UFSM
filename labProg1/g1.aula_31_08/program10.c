#include <stdio.h>

int main(int argc, char const *argv[]) {
    int x;

    scanf("%d", &x);

    (x % 2 == 0) ? printf("Par") : printf("Impar");

    return 0;
}
