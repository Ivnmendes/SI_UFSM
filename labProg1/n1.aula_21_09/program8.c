#include <stdio.h>

int main(int argc, char const *argv[]) {
    int somaDivisores1 = 0, somaDivisores2 = 0;

    //Primeiro for: Valores do primeiro numero
    for(int num1 = 2; num1 < 1000000; num1++) {
        somaDivisores1 = 0;
        //Descobre quais são os divisores de num1 e a sua soma
        for(int div1 = 1; div1 <= num1/2; div1++) {
            if(num1 % div1 == 0) {
                somaDivisores1 += div1;
            }
        }
        //Valores do segundo numero
        for(int num2 = num1; num2 < 1000000; num2++) {
            //Testa se a soma de divisores do num1 é diferente do num2, seguindo em frente caso sim, poupando tempo de execução
            if(somaDivisores1 != num2) {
                continue;
            }
            somaDivisores2 = 0;
            //Descobre quais são os divisores de num2 e a sua soma
            for(int div2 = 1; div2 <= num2/2; div2++) {
                if(num2 % div2 == 0) {
                    somaDivisores2 += div2;
                }
            }
            if(num1 == somaDivisores2 && num2 == somaDivisores1) {
                printf("%d e %d sao amigaveis\n", num1, num2);
                break;
            }
        }
    }
    printf("fim\n");
    return 0;
}
