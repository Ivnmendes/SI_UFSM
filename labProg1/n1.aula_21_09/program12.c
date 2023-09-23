#include <stdio.h>

void imprimeTabuleiro(int x, int y) {
    int colunas = 8;
    int linhas = 8;
    //Poderia ser usada apenas uma ou nenhuma variavel, mas dessa forma o codigo fica mais legivel

    printf("Movimentos possiveis:\n");
    //Imprime as duas primeiras linhas
    printf("%5s", "");
    for(int i = 1; i <= colunas; i++) {
        printf("%5d", i);
    }
    printf("\n");
    printf("%5s"," ");
    for(int i = 1; i <= colunas * 5; i++) { //colunas * 5 representa o tamanho total da tabela, sendo 5 a largura de cada coluna
        printf("-");
    }
    printf("\n");

    //Imprime o resto do tabuleiro
    for (int i = 1; i <= linhas; i++) {
        printf("%1s%2d |", " ",i);
        for (int j = 1; j <= colunas; j++) {
            //Checa se a coluna OU a linha atual é igual aos inseridos pelo usuario, caso sim, imprime um '*', representando um possivel movimento
            if(i == x || j == y) {
                printf("%5s", "*");
            } else {
                printf("%5s", "-");
            }

        }
        printf("\n");
    }
}

int main(int argc, char const *argv[]) {
    int x, y;
    printf("Movimentos de uma Torre no xadrez!\n");
    printf("Digite a linha e a coluna em que a Torre se encontra: ");
    scanf("%d", &x);
    scanf("%d", &y);
    printf("\n");

    while (x < 1 || x > 8 || y < 1 || y > 8 ) {
        printf("Valor(es) invalido(s)! (Os valores devem estar entre 1 e 8, com os mesmos inclusos)\n");

        printf("Digite a linha e a coluna em que a Torre se encontra:");
        scanf("%d", &x);
        scanf("%d", &y);
        printf("\n");
    }
    imprimeTabuleiro(x,y);
    return 0;
}
