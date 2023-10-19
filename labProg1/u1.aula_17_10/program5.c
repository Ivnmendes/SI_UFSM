#include <stdio.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    char s1[30], s2[30];

    // Le a string
    fgets(s1, sizeof(s1), stdin);

    strcpy(s2, s1);

    for (int i = 0; i < strlen(s2); i++) 
    {
        if(s2[i] == ' ') {
            s2[i] = '*';
        }
    }
    
    puts(s2);
    return 0;
}
