#include <stdio.h>
#include <string.h>

int verificarStringIguais(char s1[], char s2[]) {
    int result = 1;

    for (int i = 0; i < strlen(s1); i++)
    {
        if(s1[i] != s2[i]){
            result = 0;
        }
    }
    
    return result;
}

int main(int argc, char const *argv[])
{
    char s1[10], sInvertida[10];
    fgets(s1, sizeof(s1), stdin);


    // Remova o caractere de nova linha, se houver
    if (s1[strlen(s1) - 1] == '\n') {
        s1[strlen(s1) - 1] = '\0';
    }
    
    // Inicialize sInvertida com caracteres nulos
    for (int i = 0; i < sizeof(sInvertida); i++) {
        sInvertida[i] = '\0';
    }
    
    for (int i = 0, j = strlen(s1) - 1; i < strlen(s1); i++)
    {
        sInvertida[j] = s1[i];
        j--;
    }
    
    printf("String original: %s \n", s1);
    printf("String invertida: %s \n", sInvertida);

    if(verificarStringIguais(s1, sInvertida) == 1) {
        printf("Palindromos!");
    } else {
        printf("Nao palindromos!");
    }
    
    return 0;
}
