#include <stdio.h>
#include <string.h>

void inserirString (char s1[], char s2[], int pos) {
    strncat(s1, s2, pos);
}

int main(int argc, char const *argv[])
{
    char s1[30], s2[30];
    int pos;

    // Le as strings
    gets(s1);
    gets(s2);

    scanf("%d", &pos);

    inserirString(s1, s2, pos);
    puts(s2);
    return 0;
}
