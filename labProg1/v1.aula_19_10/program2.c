#include <stdio.h>

void func (int n, int *p1, int *p2) {
    int maiorP, menorP;
    for (int i = n - 1; i > 0; i--) {
        printf("A\n");
        int contDiv = 2;
        for (int j = 2; j <= i/2; j++) {
            if (i % j == 0) {
                contDiv++;
            }

            if (contDiv > 2) {
                break;
            }
        }

        if (contDiv == 2) {
            maiorP = i;
            break;
        }
    }

    for (int i = n + 1; i < i * 2; i++) {
        
        int contDiv = 2;
        for (int j = 2; j <= i/2; j++) {
            if (i % j == 0) {
                contDiv++;
            }

            if (contDiv > 2) {
                break;
            }
        }

        if (contDiv == 2) {
            menorP = i;
            break;
        }
    }

    *p1 = maiorP;
    *p2 = menorP;
}

int main(int argc, char const *argv[])
{
    int n, p1, p2;

    scanf("%d", &n);

    func(n, &p1, &p2);

    printf("Maior primo: %d\n", p1);
    printf("Menor primo: %d\n", p2);
    return 0;
}
