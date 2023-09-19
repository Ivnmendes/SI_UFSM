#include <stdio.h>

int main(int argc, char const *argv[]) {
    int x, y, mdc = 1, div = 2, check = 0;

    scanf("%d", &x);
    scanf("%d", &y);

    do {
        if(x % div == 0 && y % div == 0) {
            x /= div;
            y /= div;
            mdc *= div;
        } else if(x % div == 0) {
            x /= div;
        } else if (y % div == 0){
            y /= div;
        } else {
            div++;
        }

        if(x == 1 || y == 1) {
            check = 1;
        }
    } while(check != 1);

    printf("MDC: %d\n", mdc);
    return 0;
}
