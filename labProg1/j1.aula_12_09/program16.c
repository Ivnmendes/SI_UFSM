#include <stdio.h>

int main(int argc, char const *argv[])
{
    int n, t1 = 0, t2 = 1;
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        printf("%d %d ", t1, t2);

        t1 += t2;
        t2 += t1;
    }
    return 0;
}
