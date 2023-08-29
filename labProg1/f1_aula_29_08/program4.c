#include <stdio.h>

int main(int argc, char const *argv[]) {
    float pAlcool, pGasolina, kmLAlcool, kmLGasolina;

    printf("Insira o valor do litro de alcool: ");
    scanf("%f", &pAlcool);
    printf("Insira o valor do litro de gasolina: ");
    scanf("%f", &pGasolina);
    printf("Insira os quilometros por litro feito com alcool: ");
    scanf("%f", &kmLAlcool);
    printf("Insira os quilometros por litro feito com Gasolina: ");
    scanf("%f", &kmLGasolina);

    if(kmLAlcool * pAlcool > kmLGasolina * pGasolina)
        printf("A gasolina e mais economica!");
    else if(kmLAlcool * pAlcool < kmLGasolina * pGasolina)
        printf("O alcool e mais economico!");
    else
        printf("Mesmo valor, logo gasolina foi usada");

    return 0;
}
