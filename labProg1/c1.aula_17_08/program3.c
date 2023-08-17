#include <stdio.h>

int main(int argc, char const *argv[]) {
    printf("Insira a temperatura em celsius: ");
    float celsius;
    scanf("%f", &celsius);

    float fahrenheit = celsius * 1.8 + 32;
    printf("Temperatura em fahrenheit: %.1f", fahrenheit);
    return 0;
}
