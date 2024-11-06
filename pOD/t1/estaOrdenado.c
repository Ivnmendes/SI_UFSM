/* Codigo de IA*/
/* ./estaOrdenado.out txts/resultBQ.txt */
#include <stdio.h>
#include <stdlib.h>

int isSorted(const char *fileName) {
    FILE *file = fopen(fileName, "r");

    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s.\n", fileName);
        return 0; // Retorna falso se o arquivo não puder ser aberto
    }

    int prev, current;
    if (fscanf(file, "%d", &prev) != 1) {
        fprintf(stderr, "Erro ao ler o arquivo ou o arquivo está vazio.\n");
        fclose(file);
        return 0; // Retorna falso se não houver números no arquivo
    }

    while (fscanf(file, "%d", &current) == 1) {
        if (current < prev) {
            fclose(file);
            return 0; // Se encontrar um número menor que o anterior, retorna falso
        }
        prev = current; // Atualiza o valor anterior
    }

    fclose(file);
    return 1; // Retorna verdadeiro se o arquivo estiver ordenado
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <arquivo.txt>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (isSorted(argv[1])) {
        printf("O arquivo está ordenado em ordem crescente.\n");
    } else {
        printf("O arquivo não está ordenado em ordem crescente.\n");
    }

    return EXIT_SUCCESS;
}
