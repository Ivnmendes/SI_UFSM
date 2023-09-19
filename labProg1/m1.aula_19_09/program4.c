#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[]) {
    srand(time(NULL));
    int op, numSort, numEsc, totTent;

    do {
        numSort = rand() % 10;
        totTent = 0

        do {
            printf("Digite um numero: ");
            scanf("%d", &numEsc);

            totTent++;

            if(numEsc != numSort)
                printf("Errou!\n");
        } while(numEsc != numSort);

        printf("Voce acertou, o numero era: %d\n", numSort);
        printf("Total de tentativas: %d\n", totTent);

        printf("\nDigite 1 para jogar novamente: ");
        scanf("%d", &op);
    } while(op == 1);
    return 0;
}
