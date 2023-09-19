#include <stdio.h>
#include <math.h>
#include <ctype.h>

float areaRetangulo() {
    float b, h;

    printf("Insira a base: ");
    scanf("%f", &b);
    printf("Insira a altura: ");
    scanf("%f", &h);

    if(b > 0 && h > 0) {
        printf("A area do retangulo e: %.1f", b * h);
    } else {
        printf("O valor da base/altura deve ser positivo!");
    }
}

float areaQuadrado() {
    float l;

    printf("Insira o valor do lado: ");
    scanf("%f", &l);

    if(l > 0) {
        printf("A area do retangulo e: %.1f", l * l);
    } else {
        printf("O valor dos lados devem ser positivos!");
    }
}

float areaTriangulo() {
    float l1, l2, l3, semiP;

    printf("Insira o valor do lado 1: ");
    scanf("%f", &l1);
    printf("Insira o valor do lado 1: ");
    scanf("%f", &l2);
    printf("Insira o valor do lado 1: ");
    scanf("%f", &l3);

    if(l1 > 0 && l2 > 0 && l3 > 0) {
        semiP = (l1 + l2 + l3) / 2;
        printf("A area do retangulo e: %.1f", sqrt(semiP * (semiP - l1) * (semiP - l2) * (semiP - l3)));
    } else {
        printf("O valor dos lados devem ser positivos!");
    }
}

float areaTrapezio() {
    float b1, b2, h;

    printf("Insira a base menor: ");
    scanf("%f", &b1);
    printf("Insira a base maior: ");
    scanf("%f", &b2);
    printf("Insira a altura: ");
    scanf("%f", &h);

    if(b1 > 0 && b2 > 0 && h > 0) {
        printf("A area do trapezio e: %.1f", (b1+b2) * h / 2);
    } else {
        printf("O valor da base/altura deve ser positivo!");
    }
}

int main(int argc, char const *argv[]) {
    char op;

    printf(
        "Calculo de areas:\n"
        "q - area do quadrado\n"
        "r - area do retangulo\n"
        "t - area do triangulo\n"
        "p - area do trapezio\n"
        ">Selecione uma opcao: "
    );
    scanf(" %c", &op);

    switch (tolower(op)) {
        case 'q':
            areaQuadrado();
            break;
        case 'r':
            areaRetangulo();
            break;
        case 't':
            areaTriangulo();
            break;
        case 'p':
            areaTrapezio();
            break;
        default:
            printf("Opcao invalida\n");
            break;
    }

    return 0;
}
