#include <stdio.h>

int main() {
    float vMpSegundo;
    int vKmpHora;

    printf("Insira a velocidade em metros por segundo: ");
    scanf("%f", &vMpSegundo);

    vKmpHora = (int) (vMpSegundo * 3.6);

    printf("A velocidade em Km/h e de %d", vKmpHora);
    return 0;
}