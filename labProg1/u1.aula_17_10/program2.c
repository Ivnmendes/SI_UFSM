#include <stdio.h>

int main(int argc, char const *argv[])
{
    char s1[8], c1;
    int cont = 0;
    fgets(s1, 8, stdin);
    scanf(" %c", &c1);

    for (int i = 0; i < sizeof(s1); i++)
    {
        if (s1[i] == c1) {
            cont++;
        }
    }
    
    int vetP[cont];

    for (int i = 0, j = 0; i < sizeof(s1); i++)
    {
        if (s1[i] == c1) {
            vetP[j] = i;
            j++;
        }
    }

    printf("\nVetor posicao: ");
    for (int i = 0; i < cont; i++)
    {
        printf("%d ", vetP[i]);
    }
    return 0;
}
