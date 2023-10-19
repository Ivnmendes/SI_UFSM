#include <stdio.h>
#include <string.h>

char *baguncaString (char s1[], char s2[]) {
    char s3[strlen(s1) + strlen(s2)];

    for (int i = 1, j = 0; i < strlen(s1) - 1; i++, j++)
    {
        s3[j] = s1[i];
        s3[j + 1] = s2[j];
    }
    s3[strlen(s1) + strlen(s2)] = '\0';
    
    return strdup(s3);
}

char *restauraString (char s1[], char s2[]) {
    char s3[strlen(s2)];

    for (int i = 0, j = 0; i < strlen(s2); i++, j+=2)
    {
        s3[i] = s1[j];
    }
    s3[strlen(s2)] = '\O';

    return strdup(s3);
}

int main(int argc, char const *argv[])
{
    char s1[20], s2[20];

    printf("Digite a primeira string: ");
    gets(s1);

    printf("Digite a segunda string: ");
    gets(s2);

    char s3[strlen(s1) + strlen(s2)];

    for (size_t i = 0; i < strlen(s1); i++)
    {
        s3[i * 2] = s1[i];
        s3[i * 2 + 1] = s2[i];
    }
    printf("String baguncada: %s\n", s3);

    char s4[strlen(s2)];

    for (size_t i = 0, j = 0; j < strlen(s3) && i < strlen(s2); i++, j+=2)
    {
        s4[i] = s3[j];
    }

    printf("String restaurada: %s\n", s4);

    return 0;
}
