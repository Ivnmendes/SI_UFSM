#include <stdio.h>

int main(int argc, char const *argv[]) {
    int x;
    float y;
    double z;

    scanf("%d", &x);
    scanf("%f", &y);
    scanf("%lf", &z);

    printf("%d\n", x);
    printf("%.3f\n", y);
    printf("%.4lf", z);
    return 0;
}
