#include <stdio.h>

int main(int argc, char const *argv[])
{
    char strings[10][20];
    int maiorP = 0, vetP[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, tamanho;

    // Recebe as strings
    for (int i = 0; i < 10; i++)
    {
        fgets(strings[i], sizeof(strings[i]), stdin);
    }

    for (int i = 0; i < 10; i++)
    {
        tamanho = 0;
        for (int j = 0; j < sizeof(strings[i]); j++)
        {
            if (strings[i][j] == '\0')
            {
                break;
            } else {
                tamanho++;
            }
        }

        vetP[i] = tamanho;
        if (tamanho > vetP[maiorP]) {
            maiorP = i;
        }
    }

    // Escreve o vetor p
    printf("Vetor p: [");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", vetP[i]);
    }
    printf("]\n");

    printf("Maior palavra: %s com tamanho de %d", strings[maiorP], vetP[maiorP]);
    return 0;
}
