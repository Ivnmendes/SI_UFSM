#include <stdio.h>

float valorEstacionamento(int minutosTranscorridos) {
    float valorPago;

    if(minutosTranscorridos <= 60) {
        minutosTranscorridos = 60;
        valorPago = minutosTranscorridos/60 * 1.;
    }
    else if(minutosTranscorridos <= 120) {
        minutosTranscorridos = 120;
        valorPago = minutosTranscorridos/60 * 1;
    }
    else if(minutosTranscorridos <= 180) {
        minutosTranscorridos = 180;
        valorPago = minutosTranscorridos/60 * 1.4;
    }
    else if(minutosTranscorridos <= 240) {
        minutosTranscorridos = 240;
        valorPago = minutosTranscorridos/60 * 1.4;
    }
    else if (minutosTranscorridos <= 300) {
        minutosTranscorridos = 300;
        valorPago = minutosTranscorridos/60 * 2.;
    }
    else {
        valorPago = minutosTranscorridos/60 * 2.;
    }

    return valorPago;
}

int main(int argc, char const *argv[]) {
    int hChegada, mChegada, hSaida, mSaida, tSaidaMinutos, tEntradaMinutos, tEstacionamento;

    printf("Insira o horario de chegada (hh mm)");
    scanf("%d", &hChegada);
    scanf("%d", &mChegada);

    printf("Insira o horario de saida (hh mm)");
    scanf("%d", &hSaida);
    scanf("%d", &mSaida);

    if(hChegada >= 0 && hChegada <= 23 && mChegada >= 0 && mChegada <= 59 && hSaida >= 0 && hSaida <= 23 && mSaida >= 0 && mSaida <= 59 ) {
        tEntradaMinutos = hChegada * 60 + mChegada;
        tSaidaMinutos = hSaida * 60 + mSaida;

        if(tEntradaMinutos > tSaidaMinutos) {
            tSaidaMinutos += 24*60;
        }

        printf("Valor pago: R$%.2f", valorEstacionamento(tSaidaMinutos - tEntradaMinutos));
    } else {
        printf("Insira um horario valido!");
    }
    return 0;
}
