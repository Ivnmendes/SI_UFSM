#include <stdio.h>

int main(int argc, char const *argv[])
{
    int n, contDiv = 0;
    scanf("%d", &n);

    for(int i = 1; i <= n; i++) {
        if (n % i == 0) {
            contDiv++;
        }
    }

    if(contDiv > 2) {
        for(int i = 1; i <= n; i++) {
        if (n % i == 0) {
            printf("%d ", i);
        }
    }
    } else {
        printf("%d e primo", n);
    }
    return 0;
}
