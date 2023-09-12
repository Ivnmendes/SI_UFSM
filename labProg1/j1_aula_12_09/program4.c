#include <stdio.h>

int main(int argc, char const *argv[])
{
    int min, max, intervalo;

    scanf("%d", &min);
    scanf("%d", &max);
    scanf("%d", &intervalo);

    for(int i = min; i <= max; i += intervalo) {
        printf("\nGraus Celsius: %d ", i);
        printf("| Graus Fahrenheit: %.2f", (float) i * 9/5 + 32);
    }
    return 0;
}
