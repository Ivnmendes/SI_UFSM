#include <stdio.h>

int main(int argc, char const *argv[])
{
    int i, j;
    float result = 0;

    for(i = 1, j = 1; i < 100 && j < 51; i += 2, j++) {
        result += (float) i/j;
    }

    printf("%f", result);
    return 0;
}
