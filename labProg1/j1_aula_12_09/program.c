#include <stdio.h>

int soma(int n) {
    int result = 0;

    for(int i = 1; i<=n; i++) {
        result += i;
    }
    return result;
}

int main()
{
    int n;
    scanf("%d", &n);

    printf("%d", soma(n));
    return 0;
}
