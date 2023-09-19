#include <stdio.h>
#include <ctype.h>

/*  blip = 3 segundos
    tak = 40 blip
    salek = 15 tak
    mazel = 30 salek
    brat = 8 mazel
    ano = 73 brat

    O mes usado tem 30 dias
*/

int main(int argc, char const *argv[]) {
    int tTotalBlip, tTotalSeg, dia, mes, hora, min, seg, brat, mazel, salek, tak, blip;
    char op;

    printf("Bem vindo ao sistema de conversao termopilita\n-----------------------------------\n");
    printf("Escolha uma opcao para ser realizada\nA) Converte de terrestre para termopilita\nB)Converte de termopilita para terrestre (brat mazel salek tak blip)\nC) constroi uma tabela de conversoes padroes\n");
    printf("Insira a opcao escolhida: ");
    scanf(" %c", &op);

    switch (tolower(op)) {
        case 'a':
            printf("Insira a data (dia mes hora min seg): ");
            scanf("%d", &dia);
            scanf("%d", &mes);
            scanf("%d", &hora);
            scanf("%d", &min);
            scanf("%d", &seg);

            tTotalSeg = seg + min * 60 + hora * 60 * 60 + dia * 24 * 60 * 60 + mes * 30 * 24 * 60 * 60;
            blip = tTotalSeg / 3;
            brat = blip / (40*15*30*8);
            mazel = blip % (40*15*30*8) / (30 * 15 * 40);
            salek = blip % (40*15*30*8) % (30 * 15 * 40) / (15 * 40);
            tak = blip % (40*15*30*8) % (30 * 15 * 40) % (15 * 40) / (40);
            blip = blip % (40*15*30*8) % (30 * 15 * 40) % (15 * 40) % (40);

            printf("blip: %d\n tak: %d\nsalek: %d\nmazel: %d\nbrat: %d", blip, tak, salek, mazel, brat);

            break;
        case 'b':
            printf("Insira a data (brat mazel salek tak blip)");
            scanf("%d", &brat);
            scanf("%d", &mazel);
            scanf("%d", &salek);
            scanf("%d", &tak);
            scanf("%d", &blip);

            tTotalBlip = blip + tak * 40 + salek * 15 * 40 + mazel * 30 * 15 * 40 + brat * 8 * 30 * 15 * 40;
            seg = tTotalBlip * 3;
            mes = seg / (30 * 24 * 60 * 60);
            dia = seg % (30 * 24 * 60 * 60) / (24 * 60 * 60);
            hora = seg % (30 * 24 * 60 * 60) % (24 * 60 * 60) / 3600;
            min =  seg % (30 * 24 * 60 * 60) % (24 * 60 * 60) % 3600 / 60;
            seg = seg % (30 * 24 * 60 * 60) % (24 * 60 * 60) % 3600 % 60;

            printf("dia: %d\n mes: %d\nhora: %d\nmin: %d\nseg: %d", dia, mes, hora, min, seg);
            break;
        case 'c':
            printf("----------------------------\n|15 segundos = %d blip\n|2 minutos = %d tak\n|15 horas = %d salek\n|5 dias = %d mazel\n----------------------------", 15/3, (2*60/3) / 40, (15*60*60/3) / 40 / 15, (5*24*60*60/3) / 40 / 15 / 30);

            break;
        default:
            break;
    }

    return 0;
}
