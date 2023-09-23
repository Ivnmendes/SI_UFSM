#include <stdio.h>

char checkPar(int n) {
    char par = 'N';
    if(n % 100 % 10 % 2 == 0) {
        par = 'S';
    }

    return par;
}

int main(int argc, char const *argv[]) {
    int num;
    scanf("%d", &num);
    
    while (num / 100 >= 1 && num / 100 <= 9) {
        printf("%c\n", checkPar(num));
        printf("\n");
        scanf("%d", &num);
    }

    return 0;
}
