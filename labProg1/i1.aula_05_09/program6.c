#include <stdio.h>

char verificarAlbum() {
    int lA, cA, lF1, cF1, lF2, cF2;

    printf("Insira as medias do album (largura e comprimento)\n");
    scanf("%d", &lA);
    scanf("%d", &cA);
    printf("Insira as medias da primeira foto (largura e comprimento)\n");
    scanf("%d", &lF1);
    scanf("%d", &cF1);
    printf("Insira as medias da segunda foto (largura e comprimento)\n");
    scanf("%d", &lF2);
    scanf("%d", &cF2);

    if(lA > 0 && cA > 0 && lF1 > 0 && cF1 > 0 && lF2 > 0 && cF2 > 0) {
        if((lA >= lF1 + lF2 && cA > cF1 && cA > cF2) || (lA >= cF1 + cF2 && cA > lF1 && cA > lF2) || (lA >= lF1 + cF2 && cA > cF1 && cA > lF2) || (lA >= cF1 + lF2 && cA > lF1 && cA > cF2) || (cA >= lF1 + lF2 && lA > cF1 && lA > cF2) || (cA >= cF1 + cF2 && lA > lF1 && lA > lF2) || (cA >= lF1 + cF2 && lA > cF1 && lA > lF2) || (cA >= cF1 + lF2 && lA > lF1 && lA > cF2)) {
            printf("S");
        } else {
            printf("N");
        }
    } else {
        printf("As medias das fotos devem ser positivas\n");
    }
}

int main(int argc, char const *argv[]) {
    verificarAlbum();
    return 0;
}
