#include <stdio.h>

int main(int argc, char const *argv[])
{
    int matricula;
    float nota1, nota2, nota3, media;

    for(int i = 0; i < 10; i++) {
        scanf("%d", &matricula);
        scanf("%f", &nota1);
        scanf("%f", &nota2);
        scanf("%f", &nota3);

        media = (nota1*4+nota2*3+nota3*3) / 10;

        printf("Matricula: %d\nNota 1: %.1f\nNota 2: %.1f\nNota 3: %.1f\nMedia: %.1f\n", matricula, nota1, nota2, nota3, media);
        if(media >= 7)
            printf("Aprovado\n");
        else
            printf("Reprovado\n");
    }
    return 0;
}
