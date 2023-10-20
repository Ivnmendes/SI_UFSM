#include <stdio.h>
#include <string.h>

void removerCRepetido (char s1[]) {
    for (size_t i = 0; i < strlen(s1); i++) {
        for (size_t j = i+1; j < strlen(s1); j++) {
            if (s1[i] == s1[j]) {
                for (size_t k = j; k < strlen(s1); k++) {
                    s1[k] = s1[k+1];
                }
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    char s1[15];

    printf("Digite uma string: ");
    gets(s1);

    removerCRepetido(s1);

    printf("String sem caracteres repetidos: %s\n", s1);
    return 0;
}
