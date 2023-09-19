#include <stdio.h>

int checarInterseccao () {
    int r1x0, r1y0, r1x1, r1y1;
    int r2x0, r2y0, r2x1, r2y1;

    printf("Insira os valores do primeiro retangulo: ");
    scanf("%d", &r1x0);
    scanf("%d", &r1y0);
    scanf("%d", &r1x1);
    scanf("%d", &r1y1);

    printf("Insira os valores do segundo retangulo: ");
    scanf("%d", &r2x0);
    scanf("%d", &r2y0);
    scanf("%d", &r2x1);
    scanf("%d", &r2y1);

    if((r1x0 >= 0 && r1x0 < r1x1 && r1x1 <= 1000000) && (r1y0 >= 0 && r1y0 < r1y1 && r1y1 <= 1000000) && (r2x0 >= 0 && r2x0 < r2x1 && r2x1 <= 1000000) && (r2y0 >= 0 && r2y0 < r2y1 && r2y1 <= 1000000)) {
        if(((r2x0 >= r1x0 && r2x0 <= r1x1) && (r2y0 >= r1y0 && r2y0 <= r1y1)) || ((r1x0 >= r2x0 && r1x0 <= r2x1) && (r1y0 >= r2y0 && r1y0 <= r2y1))) {
            printf("1");
        } else {
            printf("0");
        }
    } else {
        printf("Valor invalido!");
    }
}

int main(int argc, char const *argv[]) {
    checarInterseccao();
    return 0;
}
