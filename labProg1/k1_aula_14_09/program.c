#include <stdio.h>

char checkPrimo(int num) {
    char primo;
    int contDiv = 0;
    for(int i = 1; i <= num; i++) {
        if(num % i == 0) {
            contDiv++;
        }
        if(contDiv > 2) {
            break;
        }
    }

    if(contDiv <= 2) {
        primo = 's';
    } else {
        primo = 'n';
    }

    return primo;
}

int main(int argc, char const *argv[]) {
    int cont = 0, num;

    printf("Insira um numero\n");
    scanf("%d", &num);

    while(num != 0) {
        if(checkPrimo(num) == 's') {
            cont++;
        }

        printf("Insira um numero\n");
        scanf("%d", &num);
    }

    printf("Total de numeros primos: %d\n", cont);
    return 0;
}
