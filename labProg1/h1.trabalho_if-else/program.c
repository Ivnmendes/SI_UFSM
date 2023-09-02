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
    " a. Validacao de data\n"
    " b. Diferenca de horarios\n"
    " c. Conversao de temperatura\n"
    " d. Calculo de material\n"
    ">Selecione uma opcao: "
    );

    scanf(" %c", &op);

    switch (op) {
        case 'a': case 'A':
            printf("\nA > Validacao de data\n");
            printf("Dia: ");
            scanf("%d", &dia);
            printf("Mês: ");
            scanf("%d", &mes);
            printf("Ano: ");
            scanf("%d", &ano);

            if(dia >= 1 && ano >= 0) {
                switch (mes) {
                    case 2:
                        dataValida = ((dia <= 28) || (dia <= 29 && (ano % 400 == 0 || ano % 4 == 0 && ano % 100 != 0))) ? 't' : 'f';
                        break;
                    case 1: case 3: case 5: case 6: case 8: case 10: case 12:
                        dataValida = (dia<= 31) ? 't' : 'f';
                        break;
                    case 4: case 7: case 9: case 11:
                        dataValida = (dia<= 30) ? 't' : 'f';
                        break;
                }

                if(dataValida == 't') {
                    printf(
                        "1. DD/MM/YYYY\n"
                        "2. YYYY-MM-DD\n"
                        "3. DD de [MES] de YYYY\n"
                        "Selecione uma opcao: "
                        );

                    scanf("%d", &opFormatacao);

                    switch (opFormatacao) {
                        case 1:
                            printf("%02d/%02d/%d", dia, mes, ano);
                            break;
                        case 2:
                            printf("%d-%02d-%02d", ano, mes, dia);
                            break;
                        case 3:
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
                            break;
                        default:
                            printf("Opcao Invalida!");
                            break;
                    }
                    printf("\n* fim *");
                } else {
                    printf("Data invalida\n");
                }
            } else {
                printf("Data invalida\n");
            }
            break;
        case 'b': case 'B':
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
                    switch (opCalcHora) {
                        case 1:
                            if(hora1 * 60 + min1 >= hora2 * 60 + min2) {
                                tTotal2 += 86400; //Adição de um dia (em segundos)
                                printf("%d horas e %d minutos", (tTotal2 - tTotal1) / 3600, (tTotal2 - tTotal1) % 3600 / 60);
                            } else {
                                printf("%d horas e %d minutos", (tTotal2 - tTotal1) / 3600, (tTotal2 - tTotal1) % 3600 / 60);
                            }
                            break;
                        case 2:
                            if(hora1 * 60 + min1 >= hora2 * 60 + min2) {
                                tTotal2 += 86400;
                                printf("%dm", (tTotal2 - tTotal1) / 60);
                            } else {
                                printf("%dm", (tTotal2 - tTotal1) / 60);
                            }
                            break;
                        case 3:
                            if(hora1 * 60 + min1 >= hora2 * 60 + min2) {
                                tTotal2 += 86400;
                                printf("%ds", tTotal2 - tTotal1);
                            } else {
                                printf("%ds", tTotal2 - tTotal1);
                            }
                            break;
                        case 4:
                            if(hora1 * 60 + min1 >= hora2 * 60 + min2) {
                                tTotal2 += 86400;
                                printf("%dms", (tTotal2 - tTotal1) * 1000);
                            } else {
                                printf("%dms", (tTotal2 - tTotal1) * 1000);
                            }
                            break;
                        default:
                            printf("Opcao invalida!");
                            break;
                    }
                    printf("\n* fim *");
            } else {
                printf("Insira um horario valido!");
            }
            break;
        case 'c': case 'C':
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

            switch (opCalcTemp) {
                case 1:
                    printf("%.2f °C <-> %.2f °F", temp, (temp * 9/5) + 32);
                    break;
                case 2:
                    printf("%.2f °C <-> %.2f K", temp, temp + 273.15);
                    break;
                case 3:
                    printf("%.2f °C <-> %.2f °R", temp, (temp * 9/5) + 491.67);
                    break;
                default:
                    printf("Opcao invalida");
                    break;
            }
            printf("\n* fim *");
            break;
        case 'd': case 'D':
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

                switch (opMaterial) {
                    case 1:
                        tTijolos = ceil((altura * 100. * comprimento * 100.) /  (266.));
                        printf("%d unidades (R$ %.2f)", tTijolos, (float) tTijolos * 400. / 1000.);
                        break;
                    case 2:
                        tTijolos = ceil((altura * 100 * comprimento * 100) /  (361));
                        printf("%d unidades (R$ %.2f)", tTijolos, tTijolos * 780.5 / 1000.);
                        break;
                    case 3:
                        tTijolos = ceil((altura * 100 * comprimento * 100) /  (551));
                        printf("%d unidades (R$ %.2f)", tTijolos, tTijolos * 899.9 / 1000.);
                        break;
                    default:
                        printf("Opcao Invalida!");
                        break;
                }
                printf("\n* fim *");
            } else {
                printf("Medidas Invalidas\n");
            }
            break;
        default:
            printf("Opcao invalida!");
            break;
    }

    return 0;
}
