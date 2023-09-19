#include <stdio.h>

float func(int n) {
    float result = 0;
    for(int i = 1; i <= n; i++) {
        if(i % 2 == 0) {
            result -= 1 / (float) i;
        } else {
            result += 1 / (float) i;
        }
    }

    return result;
}

int main(int argc, char const *argv[])
{
    int n;
    scanf("%d", &n);

    printf("%f", func(n));
    return 0;
}