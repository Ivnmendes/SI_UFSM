#include <stdio.h>

float func(int n) {
    float result = 0;
    for(int i = 1; i <= n; i++) {
        result += 1/ (float) i;
    }

    return result;
}

int main()
{
    int n;
    scanf("%d", &n);

    printf("%f", func(n));
    return 0;
}