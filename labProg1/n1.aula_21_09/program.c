#include <stdio.h>

void goldbach(int n) {
    int soma, cont1 = 0, cont2 = 0;
    for (int i = 1; i < n; i++) {   //Loops i e j para os numeros que serao somados
        for(int j = 1; j < n; j++){
            //Ambos os loops com a variavel h verificam se i e j são primos
            for(int h = 1; h <= i; h++) {
                if(i % h == 0) {
                    cont1++;
                }
                if(cont1 > 2) {
                    break;
                }
            }
            for(int h = 1; h <= j; h++) {
                if(j % h == 0) {
                    cont2++;
                }
                if(cont2 > 2) {
                    break;
                }
            }

            //Verifica o numero de divisores de i e j, se forem menores que 2 são primos, então são somados
            if(cont1 <= 2 && cont2 <= 2) {
                soma = i + j;
            }
            //Verifica se o valor da soma é igual ao numero inserido
            if(soma == n) {
                printf("%d + %d = %d\n", i, j, n);
            }

            //Zera as variáveis
            soma = 0;
            cont1 = 0, cont2 = 0;
        }
    }
}

int main(int argc, char const *argv[]) {
    int num;

    scanf("%d", &num);
    while(num % 2 == 0 && num > 0) {
        goldbach(num);

        scanf("%d", &num);
    }
    return 0;
}
