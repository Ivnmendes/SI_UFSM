#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char s1[40], s2[40];
    int k;

    fgets(s1, sizeof(s1), stdin);
    scanf("%d", &k);

    strcpy(s2, s1);

    for (int i = 0; i < strlen(s2); i++)
    {
        s2[i] = s1[i] + k;
    }
    
    puts(s2);

    return 0;
}
