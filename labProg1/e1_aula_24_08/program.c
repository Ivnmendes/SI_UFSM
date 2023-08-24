#include <stdio.h>

int main(int argc, char const *argv[]) {
    int a,b;

    scanf("%d",&a);
    scanf("%d",&b);

    if(a % b == 0 && b % a == 0) {
        printf("Ambos sao multiplos um do outro\n");
    } else if (a % b == 0) {
        printf("a e multiplo de b\n");
    } else if (b % a == 0){
        printf("b e multiplo de a\n");
    } else {
        printf("Nao sao multiplos\n" );
    }

    return 0;
}
