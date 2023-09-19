#include <stdio.h>

int fCalc(int num1, int num2) {
    int soma = num1;
    for(int i = 1; i < num2; i++) {
        soma += num1 + i;
    }

    return soma;
}

int main(int argc, char const *argv[]) {
    int op = 1, m, n;

    while(op != 0) {
        printf("\nInsira os valores: ");
        scanf("%d", &m);
        scanf("%d", &n);

        printf("Resultado: %d\n", fCalc(m,n));
        printf("Digite 0 para sair ou qualquer numero para continuar: ");
        scanf("%d", &op);
    }
    return 0;
}
