#include <stdio.h>

void func(int n, int inc) {
    for(int i = 0; i <= n; i += inc) {
        printf("%d ", i);
    }
}

int main(int argc, char const *argv[])
{
    int n, i;
    scanf("%d", &n);
    scanf("%d", &i);

    func(n,i);

    return 0;
}
