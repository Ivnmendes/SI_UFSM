#include <stdio.h>
#include <ctype.h>

float calcIngresso() {
    float ingresso, valorAlterado = 0;
    char dia, aoVivo;

    printf("Insira o valor padrao da entrada: ");
    scanf("%f", &ingresso);
    printf("Insira o dia da semana (’D’, ‘2’, ‘3’, ‘4’, ‘5’, ‘6’, ‘S’): ");
    scanf(" %c", &dia);
    printf("Havera musica ao vivo? (S,N): ");
    scanf(" %c", &aoVivo);

    switch(tolower(dia)) {
        case 'd': case '2': case '3':
            valorAlterado -= ingresso * 0.25;
            break;
    }

    if(tolower(aoVivo) == 's')
        valorAlterado += ingresso * 0.15;

    return ingresso + valorAlterado;
}

int main(int argc, char const *argv[]) {
    printf("R$%.2f", calcIngresso());
    return 0;
}
