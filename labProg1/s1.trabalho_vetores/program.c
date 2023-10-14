#include <stdio.h>

//Verifica se o vetor contem tal valor, passando como argumento o tamanho do vetor o valor a ser verificado e o vetor
int verificarValorVetor (int t, float valor, float vet[]) {
    for (int i = 0; i < t; i++)
    {
        if(vet[i] == valor) {
            return 1;
        }
    }
    return 0;
}

int main()
{
    int t;

    do {
        printf("Digite t: ");
        scanf("%d", &t);
    } while (t < 0);

    float v1[t], v2[t], v3[t * 2], v4[t * 2], v5[t], v6[t], vAuxiliar[t * 2], num,  n;

    // Le os valores do vetor 1
    printf("Digite v1: ");
    for (int i = 0; i < t; i++)
    {
        scanf("%f", &num);
        while (verificarValorVetor(t, num, v1 ) == 1)
        {
            printf("Valor invalido, digite outro valor: ");
            scanf("%f", &num);
        }
        v1[i] = num;
    }

    // Le os valores do vetor 2
    printf("Digite v2: ");
    for (int i = 0; i < t; i++)
    {
        scanf("%f", &num);
        while (verificarValorVetor(t, num, v2) == 1)
        {
            printf("Valor invalido, digite outro valor: ");
            scanf("%f", &num);
        }
        v2[i] = num;
    }

    //Atribui os valores ao vetor 3
    for (int i = 0, j = 0; i < t * 2 - 1; i+=2)
    {
        if(j % 2 == 0) {
            v3[i] = v1[j];
            v3[i + 1] = v2[j];
        } else {
            v3[i] = v2[j];
            v3[i + 1] = v1[j];
        }

        j++;
    }

    printf("Digite n: ");
    scanf("%f", &n);

    //Atribui os valores ao vetor 4
    for (int i = t * 2 - 1, j = 0; i >= 0; i--)
    {
        if ((int) v3[i] % 2 == 0) {
            v4[j] = v3[i] + n;
            vAuxiliar[j] = n;
        } else {
            v4[j] = v3[i] + n * 2;
            vAuxiliar[j] = n * 2;
        }
        j++;
    }

    // Atribui os valores dos vetores 5 e 6
    for (int i = 0, j = t - 1; i < t * 2 - 1; i+=2)
    {
        if(j % 2 == 0) {
            v6[j] = v4[i] - vAuxiliar[i];
            v5[j] = v4[i + 1] - vAuxiliar[i + 1];
        } else {
            v6[j] = v4[i + 1] - vAuxiliar[i + 1];
            v5[j] = v4[i] - vAuxiliar[i];
        }
        j--;
    }
    

    // Imprime os vetores
    printf("v1: |");
    for (int i = 0; i < t; i++)
    {
        printf("%4.1f|", v1[i]);
    }
    printf("\nv2: |");
    for (int i = 0; i < t; i++)
    {
        printf("%4.1f|", v2[i]);
    }
    printf("\nv3: |");
    for (int i = 0; i < t * 2; i++)
    {
        printf("%4.1f|", v3[i]);
    }
    printf("\nv4: |");
    for (int i = 0; i < t * 2; i++)
    {
        printf("%4.1f|", v4[i]);
    }
    printf("\nv5: |");
    for (int i = 0; i < t; i++)
    {
        printf("%4.1f|", v5[i]);
    }
    printf("\nv6: |");
    for (int i = 0; i < t; i++)
    {
        printf("%4.1f|", v6[i]);
    }
    return 0;
}
