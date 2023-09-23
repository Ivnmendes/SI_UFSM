#include <stdio.h>

int main(int argc, char const *argv[]) {
    int n, pos = 1;

    do {
        scanf("%d", &n);

        if(n % pos == 0) {
            printf("N a ser impresso: %d\n", n);
        }

        pos++;
    } while(n != 0);
    return 0;
}
