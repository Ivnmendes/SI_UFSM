#include <stdio.h>

int main() {
    float cCasa, lCasa, cTerreno, lTerreno, aCasa, aTerreno;
    printf("Insira o comprimento da casa: ");
    scanf("%f", &cCasa);
    printf("Insira a largura da casa: ");
    scanf("%f", &lCasa);
    printf("Insira o comprimento do terreno: ");
    scanf("%f", &cTerreno);
    printf("Insira a largura do terreno: ");
    scanf("%f", &lTerreno);

    aCasa = cCasa * lCasa;
    aTerreno = cTerreno * lTerreno;

    printf("Area livre do terreno\nEm metros quadrados: %.1f\nEm percentual: %.1f %%", aTerreno - aCasa,100*(aTerreno - aCasa)/aTerreno);

    return 0;
}