#include <stdio.h>

int main(int argc, char const *argv[]) {
    float pont1, pont2, pont3;

    printf("Insira a pontuacao do competidor 1: ");
    scanf("%f", &pont1);
    printf("Insira a pontuacao do competidor 2: ");
    scanf("%f", &pont2);
    printf("Insira a pontuacao do competidor 3: ");
    scanf("%f", &pont3);

    if(pont1 > pont2 && pont2 > pont3 || pont3 > pont2 && pont2 > pont1)
        printf("O vice campeao foi o competidor 2, com %.1f pontos!", pont2);
    else if (pont2 > pont1 && pont1 > pont3 || pont3 > pont1 && pont1 > pont2)
        printf("O vice campeao foi o competidor 1, com %.1f pontos!", pont1);
    else
        printf("O vice campeo foi o competidor 3, com %.1f pontos!", pont3);

    return 0;
}
