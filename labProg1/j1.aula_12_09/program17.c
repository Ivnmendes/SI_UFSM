#include <stdio.h>

int main(int argc, char const *argv[])
{
    int tab, lim;

    scanf("%d", &tab);
    scanf("%d", &lim);

    for(int i = 1; i <= lim; i++) {
        printf("%d * %d = %d\n", tab, i, tab * i);
    }
    return 0;
}
