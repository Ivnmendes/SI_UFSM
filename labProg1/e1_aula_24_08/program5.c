#include <stdio.h>
#include <math.h>

int main(int argc, char const *argv[]) {
    int a, b, c, delta;
    float x1, x2;

    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);

    delta = pow(b,2) - 4 * a * c;

    if(a == 0) {
        printf("x = %d\n", b + c);
    } else if (delta < 0) {
        printf("Quando o delta é negativo nao existem raizes\n");
    } else {
        x1 = (-b + sqrt(delta)) / 2 * a;
        x2 = (-b - sqrt(delta)) / 2 * a;

        printf("x1 = %f\n", x1);
        printf("x1 = %f\n", x1);
    }

    return 0;
}
