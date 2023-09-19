#include <stdio.h>

int func(int n) {
    int result = 0;
    for(int i = 1; i <= n; i++) {
        result += 1/i;
    }

    return result;
}

int main(int argc, char const *argv[])
{
    int n;
    scanf("%d", &n);

    printf("%d", func(n));
    return 0;
}
