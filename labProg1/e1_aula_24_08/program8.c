#include <stdio.h>
#include <math.h>

int main(int argc, char const *argv[]) {
    float l1,l2,l3,sPerimetro,area;

    scanf("%f", &l1);
    scanf("%f", &l2);
    scanf("%f", &l3);

    if(l1<l2+l3 && l2<l1+l3 && l3<l1+l2) {
        sPerimetro = (l1+l2+l3)/2;
        area = sqrt(sPerimetro*(sPerimetro-l1)*(sPerimetro
            -l2)*(sPerimetro-l3));

        printf("%.2f\n", area);
    } else {
        printf("Nao formam um triangulo!\n");
    }
    return 0;
}
