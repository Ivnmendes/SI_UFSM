#include <stdio.h>

int func(int n) {
    int result = 0;
    for(int i = 1; i <= n; i++) {
        if(i % 2 == 0) {
            result -= 1/i;
        } else {
            result += 1/i;
        }
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