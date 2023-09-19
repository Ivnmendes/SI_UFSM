#include <stdio.h>

int main(int argc, char const *argv[]) {
    int x, y ,z;

    scanf("%d", &x);
    scanf("%d", &y);

    z = (x>y) ? x : y;
    printf("%d\n", z);
    return 0;
}
