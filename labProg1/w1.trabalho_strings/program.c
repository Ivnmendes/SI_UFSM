#include <stdio.h>
#include <string.h>

void string_circular(char str[], char dir, int n) {
    int tam = strlen(str);
    char sAux[tam];
    sAux[tam] = '\0';

    if (dir == 'd') {
        for (int i = 0; i < tam; i++) {
            int aux = (i + n) % tam;
            sAux[aux] = str[i];
        }
    } else {
        for (int i = 0; i < tam; i++) {
            int aux = (i - n + tam) % tam;
            sAux[aux] = str[i];
        }
    }

    strcpy(str, sAux);
}

int main()
{
    char s1[20], dir, op;
    int n;

    do {
    printf("String: ");
    scanf("%s", s1);

    printf("Direcao (\'d\' ou \'e\'): ");
    scanf(" %c", &dir);
    while (dir != 'd' && dir != 'e') {
        printf("valor invalido!\n");
        printf("Direcao (\'d\' ou \'e\'): ");
        scanf(" %c", &dir);
    }

    printf("Deslocamentos (> 0): ");
    scanf("%d", &n);
    while (n <= 0) {
        printf("valor invalido!\n");
        printf("Deslocamentos (> 0): ");
        scanf("%d", &n);
    }

    string_circular(s1, dir, n);

    printf("String final: %s\n", s1);
    printf("Continuar ('s' ou 'n'): ");
    scanf(" %c", &op);
    } while (op != 'n');

    printf("* fim *");
    return 0;
}
