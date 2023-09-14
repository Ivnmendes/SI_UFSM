#include <stdio.h>

int main(int argc, char const *argv[]) {
    int cont = 0;
    float chico = 1.5, juca = 1.10;

    while(juca < chico) {
        juca += 0.03;
        chico += 0.02;

        cont++;
    }

    printf("Foram necessarios %d anos\n", cont);
    return 0;
}
