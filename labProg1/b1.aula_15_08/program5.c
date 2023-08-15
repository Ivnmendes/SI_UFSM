#include <stdio.h>

int main(int argc, char const *argv[]) {
    char nome[4];
    int idade;
    scanf("%s", nome);
    scanf("%d", &idade);
    printf("Nome: %s\nIdade: %d", nome,idade);
    return 0;
}
