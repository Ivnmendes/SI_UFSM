#include <stdio.h>

int main(int argc, char const *argv[]) {
    printf("Insira sua idade: ");
    int idade;
    scanf("%d", &idade);

    printf("Você tem %d dias de vida.\n", idade*365);
    return 0;
}
