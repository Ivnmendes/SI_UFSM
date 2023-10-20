#include <stdio.h>
#include <string.h>

void duplicaC (char s1[]) {
    int len = strlen(s1);
    char s2[len * 2 + 1];

    for (int i = len - 1; i >= 0; i--) {
            s2[2 * i] = s1[i];
            s2[2 * i + 1] = s1[i];
        }
    s2[len * 2] = '\0';

    puts(s2);
    strcpy(s1, s2);
}

int main(int argc, char const *argv[])
{
    char s1[20];

    fgets(s1, sizeof(s1), stdin);
    s1[strcspn(s1, "\n")] = '\0';

    duplicaC(s1);

    printf("%s\n", s1);
    return 0;
}
