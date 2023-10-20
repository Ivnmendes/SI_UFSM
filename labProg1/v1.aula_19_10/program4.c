#include <stdio.h>
#include <string.h>

void inverteString (char s1[]) {
    char aux;
    for (size_t i = 0, j = strlen(s1) - 1; i < strlen(s1) - 2; i++, j--)
    {
        aux = s1[i];
        s1[i] = s1[j];
        s1[j] = aux;
    }
}

int main(int argc, char const *argv[])
{
    char s1[15];

    printf("Digite uma string: ");
    gets(s1);

    inverteString(s1);

    printf("String invertida: %s\n", s1);
    return 0;
}
