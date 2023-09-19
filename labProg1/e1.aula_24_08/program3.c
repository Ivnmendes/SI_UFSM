#include <stdio.h>
#include <math.h>

int main(int argc, char const *argv[]) {
    int num;

    scanf("%d", &num);

    if (num > 0) {
        printf("%f", 1/(double) num);
    } else {
        printf("%d\n", fabs(num));
    }
    return 0;
}
