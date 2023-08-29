#include <stdio.h>

int main(int argc, char const *argv[]) {
    int x, y;

    printf("Insira as coordenadas do ponto de contato da bola: ");

    scanf("%d", &x);
    scanf("%d", &y);

    if(x >= 0 && x <= 432 && y >= 0 && y <= 468)
        printf("A bola caiu dentro da quadra");
    else
        printf("A bola caiu fora da quadra");

    return 0;
}
