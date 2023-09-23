#include <stdio.h>

void exibeDivisores (int n){
    printf("%d ", n);
    for(int i = n/2; i >= 1; i--) {
        if(n % i == 0) {
            printf("%d ", i);
        }
    }
}

int main(int argc, char const *argv[]) {
    int op = 0, num;

    while (op != 1) {
        scanf("%d", &num);
        exibeDivisores(num);

        printf("\nDigite 1 para parar: \n");
        scanf("%d", &op);
    }
    return 0;
}
