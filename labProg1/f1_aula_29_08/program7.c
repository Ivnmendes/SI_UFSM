#include <stdio.h>

int main(int argc, char const *argv[]) {
    int ana, bob, caren;

    printf("Dois ou ... Um!\n");

    scanf("%d",&ana);
    scanf("%d",&bob);
    scanf("%d",&caren);

    printf("Ana: %d\n", ana);
    printf("Bob: %d\n", bob);
    printf("Caren: %d\n", caren);

    if(ana != bob && bob == caren)
        printf("Ana ganhou");
    else if(bob != ana && ana == caren)
        printf("Bob ganhou");
    else if(caren != bob && bob == ana)
        printf("Caren ganhou");
    else
        printf("*");

    return 0;
}
