#include <stdio.h>

int main(int argc, char const *argv[]) {
    int num;

    scanf("%d", &num);

    if(num % 3 == 0 && num % 7 == 0) {
        printf("%d e divisivel por 3 e por 7\n", num);
    } else {
        printf("%d nao e divisivel por 3 e por 7\n", num);
    }

    return 0;
}
