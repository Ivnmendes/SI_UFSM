#include <stdio.h>
#include <math.h>
/*
 * Ivan Mendes
 */

int main()
{
    char op;
    int opFormatacao, opCalcHora, opCalcTemp, opMaterial;

    char dataValida = 'f';

    int dia, mes, ano;
    int hora1, min1, hora2, min2, tTotal1, tTotal2;
    int tTijolos;
    float temp;
    float altura, comprimento;

    printf("*****************\n*      ZOXY     *\n*****************");
    printf(
    "\nMenu Inicial\n"
    "a. Validacao de data\n"
    "b. Diferenca de horarios\n"
    "c. Conversao de temperatura\n"
    "d. Calculo de material\n"
    ">Selecione uma opcao: "
    );

    scanf(" %c", &op);

    if(op == 'a' || op == 'A') {
        printf("\nA > Validacao de data\n");
        printf("Dia: ");
        scanf("%d", &dia);
        printf("Mês: ");
        scanf("%d", &mes);
        printf("Ano: ");
        scanf("%d", &ano);

        if(dia >= 1 && ano >= 0) {
            if(mes == 2 && ((dia <= 28) || (dia <= 29 && (ano % 400 == 0 || ano % 4 == 0 && ano % 100 != 0)))) {
                dataValida = 't';
            } else if((mes == 1 || mes == 3 || mes == 5 || mes == 6 || mes == 8 || mes == 10 || mes == 12) && (dia<= 31)) {
                dataValida = 't';
            } else if((mes == 4 || mes == 7 || mes == 9 || mes == 11)) {
                dataValida = 't';
            }
            if(dataValida == 't') {
                printf(
                    "1. DD/MM/YYYY\n"
                    "2. YYYY-MM-DD\n"
                    "3. DD de [MES] de YYYY\n"
                    "Selecione uma opcao: "
                    );

                scanf("%d", &opFormatacao);

                if(opFormatacao == 1) {
                    printf("%02d/%02d/%d", dia, mes, ano);
                } else if(opFormatacao == 2) {
                    printf("%d-%02d-%02d", ano, mes, dia);
                } else if(opFormatacao == 3) {
                    printf("%d de ", dia);
                    if(mes == 1) {
                        printf("janeiro");
                    } else if (mes == 2) {
                        printf("fevereiro");
                    } else if (mes == 3) {
                        printf("marco");
                    } else if (mes == 4) {
                        printf("abril");
                    } else if (mes == 5) {
                        printf("maio");
                    } else if (mes == 6) {
                        printf("junho");
                    } else if (mes == 7) {
                        printf("julho");
                    } else if (mes == 8) {
                        printf("agosto");
                    } else if (mes == 9) {
                        printf("setembro");
                    } else if (mes == 10) {
                        printf("outubro");
                    } else if (mes == 11) {
                        printf("novembro");
                    } else {
                        printf("dezembro");
                    }
                    printf(" de %d", ano);
                } else {
                    printf("Opcao Invalida!");
                }

                printf("\n* fim *");
            } else {
                printf("Data invalida\n");
            }
        } else {
            printf("Data invalida\n");
        }
    } else if(op == 'b' || op == 'B') {
        printf("\nB > Diferenca de horarios\n");
        printf("Hora 1: ");
        scanf("%d", &hora1);
        printf("Minuto 1: ");
        scanf("%d", &min1);
        printf("Hora 2: ");
        scanf("%d", &hora2);
        printf("Minuto 2: ");
        scanf("%d", &min2);

        if(hora1 >= 0 && hora1 <= 24 && min1 >= 0 && min1 <= 59 && hora2 >= 0 && hora2 <= 24 && min2 >= 0 && min2 <= 59) {
            printf(
                    "1. Padrao\n"
                    "2. Minutos\n"
                    "3. Segundos\n"
                    "4. Milisegundos\n"
                    "Selecione uma opcao: "
                    );
            scanf("%d", &opCalcHora);

            //Conversão do tempo inserido para segundos, facilitando os cálculos
            tTotal1 = hora1 * 3600 + min1 * 60;
            tTotal2 = hora2 * 3600 + min2 * 60;

            if(opCalcHora == 1) {
                if(hora1 * 60 + min1 >= hora2 * 60 + min2) {
                    tTotal2 += 86400; //Adição de um dia (em segundos)
                    printf("%d horas e %d minutos", (tTotal2 - tTotal1) / 3600, (tTotal2 - tTotal1) % 3600 / 60);
                } else {
                    printf("%d horas e %d minutos", (tTotal2 - tTotal1) / 3600, (tTotal2 - tTotal1) % 3600 / 60);
                }
            } else if (opCalcHora == 2) {
                if(hora1 * 60 + min1 >= hora2 * 60 + min2) {
                    tTotal2 += 86400;
                    printf("%dm", (tTotal2 - tTotal1) / 60);
                } else {
                    printf("%dm", (tTotal2 - tTotal1) / 60);
                }
            } else if (opCalcHora == 3) {
                if(hora1 * 60 + min1 >= hora2 * 60 + min2) {
                    tTotal2 += 86400;
                    printf("%ds", tTotal2 - tTotal1);
                } else {
                    printf("%ds", tTotal2 - tTotal1);
                }
            } else if (opCalcHora == 4) {
                if(hora1 * 60 + min1 >= hora2 * 60 + min2) {
                    tTotal2 += 86400;
                    printf("%dms", (tTotal2 - tTotal1) * 1000);
                } else {
                    printf("%dms", (tTotal2 - tTotal1) * 1000);
                }
            } else {
                printf("Opcao invalida!");
            }
            printf("\n* fim *");
        } else {
            printf("Insira um horario valido!");
        }
    } else if(op == 'c' || op == 'C') {
        printf("\nC > Diferenca de temperatura\n");
        printf("Temperatura (°C): ");
        scanf("%f", &temp);

        printf(
                "1. Fahrenheit\n"
                "2. Kelvin\n"
                "3. Rankine\n"
                "Selecione uma opcao: "
                );
        scanf("%d", &opCalcTemp);

        if(opCalcTemp == 1) {
            printf("%.2f °C <-> %.2f °F", temp, (temp * 9/5) + 32);
        } else if(opCalcTemp == 2) {
            printf("%.2f °C <-> %.2f K", temp, temp + 273.15);
        } else if(opCalcTemp == 3) {
            printf("%.2f °C <-> %.2f °R", temp, (temp * 9/5) + 491.67);
        } else {
            printf("Opcao invalida");
        }

        printf("\n* fim *");
    } else if(op == 'd' || op == 'D') {
        printf("\nD > Calculo de material\n");
        printf("Altura (m): ");
        scanf("%f", &altura);
        printf("Comprimento (m): ");
        scanf("%f", &comprimento);

        if(altura > 0 && comprimento > 0) {
            printf(
                    "1. 6 furos\n"
                    "2. 8 furos\n"
                    "3. 9 furos\n"
                    "Selecione uma opcao: "
                    );
            scanf("%d", &opMaterial);

            if(opMaterial == 1) {
                tTijolos = ceil((altura * 100. * comprimento * 100.) /  (266.));
                printf("%d unidades (R$ %.2f)", tTijolos, (float) tTijolos * 400. / 1000.);
            } else if(opMaterial == 2) {
                tTijolos = ceil((altura * 100 * comprimento * 100) /  (361));
                printf("%d unidades (R$ %.2f)", tTijolos, tTijolos * 780.5 / 1000.);
            } else if(opMaterial == 3) {
                tTijolos = ceil((altura * 100 * comprimento * 100) /  (551));
                printf("%d unidades (R$ %.2f)", tTijolos, tTijolos * 899.9 / 1000.);
            } else {
                printf("Opcao Invalida!");
            }

            printf("\n* fim *");
        } else {
            printf("Medidas Invalidas\n");
        }
    } else {
        printf("Opcao invalida!");
    }

    return 0;
}
