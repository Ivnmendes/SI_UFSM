#include <stdio.h>
#include <ctype.h>

int main(int argc, char const *argv[]) {
    float altura;
    char sexo;

    printf("Insira a altura (centimetros): ");
    scanf("%f", &altura);
    printf("Insira o sexo (M/F): ");
    scanf(" %c", &sexo);

    if(toupper(sexo) == 'M') {
        printf("%.1f", 72.7 * altura -58);
    } else if (toupper(sexo) == 'F') {
        printf("%.1f\n", 62.1 * altura -44.7);
    } else {
        printf("Valor invalido.\n");
    }

    return 0;
}
