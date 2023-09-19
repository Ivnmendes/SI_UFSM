
#include <stdio.h>

int main(int argc, char const *argv[]) {
    int num, sum = 0;
    do {
        scanf("%d", &num);
        if(num > 0)
            sum += num;
    } while(num >= 0);

    printf("Soma = %d", sum);
    return 0;
}
