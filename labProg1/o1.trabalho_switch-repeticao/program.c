#include <stdio.h>

float mediaGeralAcumulada () {
    int nDisciplinasApComNota = 0;
    float mFinalDisciplina, somaAcumulada = 0, mGA;

    printf("Insira a media da disciplina (digite um valor negativo para parar de inserir notas): ");
    scanf("%f", &mFinalDisciplina);
    //Loops responsaveis por checar se o valor e valido (negativo nao e considerado invalido por ser o comando para sair do looping)
    while(mFinalDisciplina > 10) {
        printf("O valor da media deve estar entre 0 e 10!\n");
        printf("Insira a media da disciplina (digite um valor negativo para parar de inserir notas): ");
        scanf("%f", &mFinalDisciplina);
    }

    while(mFinalDisciplina >= 0) {
        //Se aprovado na disciplina, soma o valor na variavel acumuladora e incrementa a variavel contadora
        if(mFinalDisciplina >= 7) {
            somaAcumulada += mFinalDisciplina;
            nDisciplinasApComNota++;
        }

        printf("Insira a media da disciplina (digite um valor negativo para parar de inserir notas): ");
        scanf("%f", &mFinalDisciplina);
        while(mFinalDisciplina > 10) {
            printf("O valor da media deve estar entre 0 e 10!\n");
            printf("Insira a media da disciplina (digite um valor negativo para parar de inserir notas): ");
            scanf("%f", &mFinalDisciplina);
        }
    }

    mGA = somaAcumulada / nDisciplinasApComNota;
    return mGA;
}

float indiceDeDesempenhoAcademico() {
    int cHApComNota, cHDisciplinasApSemNota, cHDisciplinasRepComNota, cHDisciplinasRepSemNota;
    float iDA, mFinal, mDisciplinaApComNota, mDasMediasDisciplinasApComNota, notaMinimaAprovacaoDisciComNota, notaMinimaAprovacaoDisciSemNota;

    printf("Insira a media final: ");
    scanf("%f", &mFinal);
    //Loops responsaveis por checar se o valor e valido
    while(mFinal > 10 || mFinal < 0) {
        printf("O valor da media deve estar entre 0 e 10!\n");
        printf("Insira a media final: ");
        scanf("%f", &mFinal);
    }

    printf("Insira a carga horaria das disciplinas aprovadas com nota: ");
    scanf("%d", &cHApComNota);
    while(cHApComNota <= 0) {
        printf("O valor da carga horaria deve ser maior que 0!\n");
        printf("Insira a carga horaria das disciplinas aprovadas com nota ");
        scanf("%d", &cHApComNota);
    }

    printf("Insira a media das medias das disciplinas aprovadas com nota: ");
    scanf("%f", &mDasMediasDisciplinasApComNota);
    while(mDasMediasDisciplinasApComNota > 10 || mDasMediasDisciplinasApComNota < 0) {
        printf("O valor da media deve estar entre 0 e 10!\n");
        printf("Insira a media das medias das disciplinas aprovadas com nota: ");
        scanf("%f", &mDasMediasDisciplinasApComNota);
    }

    printf("Insira a carga horaria das disciplinas aprovadas sem nota: ");
    scanf("%d", &cHDisciplinasApSemNota);
    while(cHDisciplinasApSemNota <= 0) {
        printf("O valor da carga horaria deve ser maior que 0!\n");
        printf("Insira a carga horaria das disciplinas aprovadas sem nota ");
        scanf("%d", &cHDisciplinasApSemNota);
    }

    printf("Insira a nota minima para aprovacao nas disciplinas reprovadas com nota: ");
    scanf("%f", &notaMinimaAprovacaoDisciComNota);
    while(notaMinimaAprovacaoDisciComNota > 10 || notaMinimaAprovacaoDisciComNota < 0) {
        printf("O valor da nota deve estar entre 0 e 10!\n");
        printf("Insira a nota minima para aprovacao nas disciplinas reprovadas com nota: ");
        scanf("%f", &notaMinimaAprovacaoDisciComNota);
    }

    printf("Insira a carga horaria das disciplinas reprovadas com nota: ");
    scanf("%d", &cHDisciplinasRepComNota);
    while(cHDisciplinasRepComNota <= 0) {
        printf("O valor da carga horaria deve ser maior que 0!\n");
        printf("Insira a carga horaria das disciplinas reprovadas com nota ");
        scanf("%d", &cHDisciplinasRepComNota);
    }

    printf("Insira a carga horaria das disciplinas reprovadas sem nota: ");
    scanf("%d", &cHDisciplinasRepSemNota);
    while(cHDisciplinasRepSemNota <= 0) {
        printf("O valor da carga horaria deve ser maior que 0!\n");
        printf("Insira a carga horaria das disciplinas reprovadas sem nota ");
        scanf("%d", &cHDisciplinasRepSemNota);
    }

    printf("Insira a nota minima para aprovacao nas disciplinas reprovadas sem nota: ");
    scanf("%f", &notaMinimaAprovacaoDisciSemNota);
    while(notaMinimaAprovacaoDisciSemNota > 10 || notaMinimaAprovacaoDisciSemNota < 0) {
        printf("O valor da nota deve estar entre 0 e 10!\n");
        printf("Insira a nota minima para aprovacao nas disciplinas reprovadas sem nota: ");
        scanf("%f", &notaMinimaAprovacaoDisciSemNota);
    }

    iDA = (mFinal * cHApComNota) + (mDasMediasDisciplinasApComNota * cHDisciplinasApSemNota) - ((notaMinimaAprovacaoDisciComNota * mFinal) * cHDisciplinasRepComNota) - (notaMinimaAprovacaoDisciSemNota * cHDisciplinasRepSemNota);
    return iDA;
}

float mediaTotalDisciplinas() {
    int cHAprovada, cHReprovada;
    float mTD, mediaDisciplinaAprovada, mediaDisciplinaReprovada, resultAprovadas = 0, resultReprovadas = 0;

    printf("\nDisciplinas aprovadas - Digite um valor negativo para parar de inserir\n");
    printf("Insira a media da disciplina aprovada: ");
    scanf("%f", &mediaDisciplinaAprovada);
    //Loops responsaveis por checar se o valor e valido (negativo nao e considerado invalido por ser o comando para sair do looping)
    while(mediaDisciplinaAprovada > 10) {
        printf("O valor da media deve estar entre 0 e 10!\n");
        printf("Insira a media da disciplina aprovada: ");
        scanf("%f", &mediaDisciplinaAprovada);
    }
    printf("Insira a carga horaria da disciplina aprovada: ");
    scanf("%d", &cHAprovada);
    while(cHAprovada == 0) {
        printf("O valor da carga horaria deve ser maior que 0!\n");
        printf("Insira a carga horaria da disciplina aprovada: ");
        scanf("%d", &cHAprovada);
    }
    while (mediaDisciplinaAprovada >= 0 && cHAprovada >= 0) {
        //Atribui os valores inseridos na variavel acumuladora
        resultAprovadas += mediaDisciplinaAprovada * cHAprovada;
        printf("Insira a media da disciplina aprovada: ");
        scanf("%f", &mediaDisciplinaAprovada);
        while(mediaDisciplinaAprovada > 10) {
            printf("O valor da media deve estar entre 0 e 10!\n");
            printf("Insira a media da disciplina aprovada: ");
            scanf("%f", &mediaDisciplinaAprovada);
        }
        printf("Insira a carga horaria da disciplina aprovada: ");
        scanf("%d", &cHAprovada);
        while(cHAprovada == 0) {
            printf("O valor da carga horaria deve ser maior que 0!\n");
            printf("Insira a carga horaria da disciplina aprovada: ");
            scanf("%d", &cHAprovada);
        }
    }

    printf("\nDisciplinas reprovadas - Digite um valor negativo para parar de inserir\n");
    printf("Insira a media da disciplina reprovada: ");
    scanf("%f", &mediaDisciplinaReprovada);
    while(mediaDisciplinaReprovada > 10) {
        printf("O valor da media deve estar entre 0 e 10!\n");
        printf("Insira a media da disciplina reprovada: ");
        scanf("%f", &mediaDisciplinaReprovada);
    }
    printf("Insira a carga horaria da disciplina reprovada: ");
    scanf("%d", &cHReprovada);
    while(cHReprovada == 0) {
        printf("O valor da carga horaria deve ser maior que 0!\n");
        printf("Insira a carga horaria da disciplina reprovada: ");
        scanf("%d", &cHAprovada);
    }
    while (mediaDisciplinaReprovada >= 0 && cHReprovada >= 0) {
        //Atribui os valores inseridos na variavel acumuladora
        resultReprovadas += mediaDisciplinaReprovada * cHReprovada;
        printf("Insira a media da disciplina reprovada: ");
        scanf("%f", &mediaDisciplinaReprovada);
        while(mediaDisciplinaReprovada > 10) {
            printf("O valor da media deve estar entre 0 e 10!\n");
            printf("Insira a media da disciplina reprovada: ");
            scanf("%f", &mediaDisciplinaReprovada);
        }
        printf("Insira a carga horaria da disciplina reprovada: ");
        scanf("%d", &cHReprovada);
        while(cHReprovada == 0) {
            printf("O valor da carga horaria deve ser maior que 0!\n");
            printf("Insira a carga horaria da disciplina reprovada: ");
            scanf("%d", &cHReprovada);
        }
    }

    mTD = resultAprovadas - resultReprovadas;
    return mTD;
}

float percentualAproveitamentoAluno() {
    int quantAprovado, quantTotal;
    float pAA;

    printf("Insira o total de disciplinas aprovadas: ");
    scanf("%d", &quantAprovado);
    while (quantAprovado <= 0) {
        printf("O valor deve ser maior que zero!\n");
        printf("Insira o total de disciplinas aprovadas: ");
        scanf("%d", &quantAprovado);
    }

    printf("Insira o total de disciplinas: ");
    scanf("%d", &quantTotal);
    while (quantTotal <= 0 || quantTotal < quantAprovado) {
        printf("O valor deve ser maior que zero e nao pode ser menor que o total de disciplinas aprovadas!\n");
        printf("Insira o total de disciplinas: ");
        scanf("%d", &quantTotal);
    }

    pAA = ((float) quantAprovado * 100) / quantTotal;
    return pAA;
}

int main(int argc, char const *argv[]) {
    int num, dV, somaP = 0, op;

    printf("Insira os ultimos 5 digitos da matricula: ");
    //Le os 5 digitos da matricula
    for (int i = 9; i >= 5; i--) {
        scanf("%d", &num);
        printf("%d", num);
        somaP += num * i;
    }

    //Define o valor do digito verificador e impressao do resto do numero de matricula
    dV = somaP * 10 % 11;
    if(dV / 10 >= 1) {
        dV = dV % 10;
    }
    printf("-%d\n", dV);

    do {
        printf("\nMenu Aluno\n"
        "1- Calculo Media Geral Acumulada (MGA)\n"
        "2- Indice de Desempenho Academico (IDA)\n"
        "3- Media Total de Disciplinas (MTD)\n"
        "4- Percentual de Aproveitamento do Aluno (PAA)\n"
        "0- Sair do programa\n"
        "Selecione uma opcao: ");
        scanf("%d", &op);
        switch (op) {
            case 0:
                break;
            case 1:
                printf("\nMGA: %.2f\n", mediaGeralAcumulada());
                break;
            case 2:
                printf("\nIDA: %f\n", indiceDeDesempenhoAcademico());
                break;
            case 3:
                printf("\nMTD: %.2f\n", mediaTotalDisciplinas());
                break;
            case 4:
                float pAA = percentualAproveitamentoAluno();
                printf("\nPAA: %.2f\n", pAA);
                if(pAA == 100) {
                    printf("Voce foi aprovada em 100%% das disciplinas, parabens!\n");
                }
                break;
            default:
                printf("Valor Invalido!\n");
                break;
        }
    } while(op != 0);
    printf("\nObrigado por usar nosso sistema!\n");
    return 0;
}
