#include <stdio.h>

void checarVencimento() {
    int dPlaca, ultimoDigito, mesAtual;

    printf("Insira o numero correspondente do mes atual");
    scanf("%d", &mesAtual);
    printf("Insira os 4 digitos da placa de seu veiculo: ");
    scanf("%d", &dPlaca);

    ultimoDigito = dPlaca % 1000 % 100 % 10;

    if(mesAtual == ultimoDigito) {
        printf("Voce deve pagar neste mes");
    } else {
        switch (ultimoDigito) {
            case 1:
                printf("Janeiro");
                break;
            case 2:
                printf("Fevereiro");
                break;
            case 3:
                printf("Marco");
                break;
            case 4:
                printf("Abril");
                break;
            case 5:
                printf("Maio");
                break;
            case 6:
                printf("Junho");
                break;
            case 7:
                printf("Julho");
                break;
            case 8:
                printf("Agosto");
                break;
            case 9:
                printf("Setembro");
                break;
            case 0:
                printf("Outubro");
                break;
        }
    }
}

int main(int argc, char const *argv[]) {
    checarVencimento();

    return 0;
}
