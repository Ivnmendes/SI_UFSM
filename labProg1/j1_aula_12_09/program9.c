#include <stdio.h>

void floyd(int n) {
    int num = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            printf("%d ", num);
            num++;
        }
        printf("\n");
    }
}

int main(int argc, char const *argv[])
{
    int n;
    scanf("%d", &n);

    floyd(n);
    return 0;
}
