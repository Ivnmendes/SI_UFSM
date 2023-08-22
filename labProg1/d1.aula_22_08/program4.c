#include <stdio.h>

#define INSS 0.08
#define IR 0.11
#define CSINDICAL 0.05

int main() {
    float valorHora, sBruto, sLiquido;
    int hTrabalhadas;
    printf("Insira o valor da hora: ");
    scanf("%f", &valorHora);
    printf("Insira o total de horas trabalhadas: ");
    scanf("%d", &hTrabalhadas);

    sBruto = valorHora * hTrabalhadas;
    sLiquido = sBruto - (sBruto * INSS) - (sBruto * IR) - (sBruto * CSINDICAL);

    printf(
        "Salario Bruto: R$%.2f"
        "\nSalario Liquido: R$%.2f"
        "\nDesconto INSS: R$%.2f"
        "\nSalario IR: R$%.2f"
        "\nContribuicao sindical: R$%.2f",
        sBruto,sLiquido,sBruto * INSS,sBruto * IR,sBruto * CSINDICAL
    );

    return 0;
}