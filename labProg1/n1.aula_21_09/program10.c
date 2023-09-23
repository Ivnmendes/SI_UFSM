#include <stdio.h>

int main(int argc, char const *argv[]) {
    int n, result, div = 2, contDiv, cont, nPrimo = 1;
    scanf("%d", &n);

    result = n;

    while(result > 1) {
        //Zera os contadores
        contDiv = 0;
        cont = 0;
        //Verifica se div é um número primo
        for(int i = 2; i < div/2; i++) {
            if(div % i) {
                nPrimo = 0;
                contDiv++;
                break;
            }
        }

        //Se nPrimo == 1 (variavel boolean) e o numero atual de result é divisivel por div realize a divisao e some 1 no contador de multiplicidade
        if(nPrimo == 1) {
            while(result % div == 0) {
                result /= div;
                cont++;
            }
        }
        //Caso o contador de multiplicidade seja maior que zero imprima o fator e o numero de vezes que ele aparece
        if(cont > 0) {
            printf("fator %d multiplicidade %d ", div, cont);
        }
        div++;
    }
    return 0;
}
