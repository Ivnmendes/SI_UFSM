#include <stdio.h>

int main(int argc, char const *argv[])
{
    char s1[10], char1, char2;
    fgets(s1, 10, stdin);
    scanf(" %c", &char1);
    scanf(" %c", &char2);

    for(int i = 0; i < sizeof(s1); i++){
        if(s1[i] == char1){
            s1[i] = char2;
        }
    }

    puts(s1);
    return 0;
}
