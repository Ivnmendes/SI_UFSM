#include <stdio.h>
#include <stdlib.h>

// codigo de ia
//./program.out txts/resultBQ.txt txts/resultBI.txt > compara.txt


void compareFiles(const char *file1, const char *file2) {
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");

    if (f1 == NULL || f2 == NULL) {
        fprintf(stderr, "Erro ao abrir os arquivos.\n");
        exit(EXIT_FAILURE);
    }

    int num1, num2;
    int position = 0;
    int areEqual = 1; // Assumimos que são iguais inicialmente

    while (fscanf(f1, "%d", &num1) == 1 && fscanf(f2, "%d", &num2) == 1) {
        if (num1 != num2) {
            printf("Diferente na posição %d: %d (arquivo 1) != %d (arquivo 2)\n", position, num1, num2);
            areEqual = 0; // Se encontrarmos uma diferença, mudamos para falso
        } else {
            printf("Igual na posição %d: %d (arquivo 1) == %d (arquivo 2)\n", position, num1, num2);
            areEqual = 1; // Se encontrarmos uma diferença, mudamos para falso
        }
        position++;
    }

    // Verifica se um arquivo tem mais números que o outro
    if (fscanf(f1, "%d", &num1) == 1) {
        printf("Arquivo %s tem números extras.\n", file1);
        areEqual = 0;
    }
    if (fscanf(f2, "%d", &num2) == 1) {
        printf("Arquivo %s tem números extras.\n", file2);
        areEqual = 0;
    }

    if (areEqual) {
        printf("Os arquivos são iguais.\n");
    } else {
        printf("Os arquivos são diferentes.\n");
    }

    fclose(f1);
    fclose(f2);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <arquivo1.txt> <arquivo2.txt>\n", argv[0]);
        return EXIT_FAILURE;
    }

    compareFiles(argv[1], argv[2]);
    return EXIT_SUCCESS;
}
