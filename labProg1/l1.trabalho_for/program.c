#include <stdio.h>
#include <time.h>

int estrategia1() {
    int ganhou = 0, perdeu = 0, cEscolhida, asDeEspadas;

    for(int i = 0; i < 1000000; i++) {
        asDeEspadas = rand() % 3; //Seleciona um valor aleatório para representar o As de espadas (entre 0 e 2).
        cEscolhida = rand() % 3; //Seleciona um valor aleatório para representar a carta escolhida pelo jogador (entre 0 e 2).

        if(cEscolhida == asDeEspadas) {
            ganhou++;
        } else {
            perdeu++;
        }
    }

    printf(
    "Estrategia 1\n"
    "Partidas jogadas: 1000000\n"
    "Partidas ganhas: %d\n"
    "Partidas perdidas: %d\n"
    "%% de derrotas %.2f%%\n"
    "%% de vitorias %.2f%%\n"
    , ganhou, perdeu, (float) perdeu * 100 / 1000000, (float) ganhou * 100 / 1000000);

    return ganhou;
}

int estrategia2() {
    int ganhou = 0, perdeu = 0, cEscolhida, asDeEspadas;

    for(int i = 0; i < 1000000; i++) {
        asDeEspadas = rand() % 3; //Seleciona um valor aleatório para representar o As de espadas (entre 0 e 2).
        cEscolhida = rand() % 3; //Seleciona um valor aleatório para representar a carta escolhida pelo jogador (entre 0 e 2).

        if(cEscolhida == asDeEspadas) {
            perdeu++;
        } else {
            ganhou++;
        }
    }

    printf(
    "\nEstrategia 2\n"
    "Partidas jogadas: 1000000\n"
    "Partidas ganhas: %d\n"
    "Partidas perdidas: %d\n"
    "%% de derrotas %.2f%%\n"
    "%% de vitorias %.2f%%\n"
    , ganhou, perdeu, (float) perdeu * 100 / 1000000, (float) ganhou * 100 / 1000000);

    return ganhou;
}

int main() {
    srand(time(NULL));

    int ganhos1 = estrategia1();
    int ganhos2 = estrategia2();

    printf("\nRecomendacao: ");
    if(ganhos1 > ganhos2) {
        printf("Estrategia 1");
    } else if(ganhos2 > ganhos1) {
        printf("Estrategia 2");
    } else {
        printf("Indiferente");
    }

    return 0;
}
