#include <stdio.h>

int main(int argc, char const *argv[]) {
    int x;
    scanf("%d", &x);

    printf("%d", x%100/10);
    return 0;
}
