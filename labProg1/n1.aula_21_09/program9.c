#include <stdio.h>

void checarMulti(int x, int y, int z) {
    int i = 1, cont = 0;
    while (cont < x) {
        if(i % y == 0 && i % z == 0) {
            printf("%d ", i);
            cont++;
        }
        i++;
    }
}

int main(int argc, char const *argv[]) {
    int n, a, b;
    scanf("%d", &n);
    scanf("%d", &a);
    scanf("%d", &b);

    checarMulti(n, a ,b);
    return 0;
}
