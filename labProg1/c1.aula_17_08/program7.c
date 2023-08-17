#include <stdio.h>

int main(int argc, char const *argv[]) {
    int data;
    scanf("%d", &data);
    printf("dia: %d\n", data/1000000);
    printf("mês: %d\n", data%1000000/10000);
    printf("ano: %d\n", data%10000);
    return 0;
}
