#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int isPositiveInteger(const char *str) {
    if (str == NULL || *str == '\0') return 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit((unsigned char)str[i])) return 0;
    }
    return atoi(str) > 0;
}

int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

void spawnProcessTree(int height, int maxHeight) {
    if (height > maxHeight) { return; }

    pid_t leftPID = fork();
    if (leftPID < 0) {
        fprintf(stderr, "Erro: fork falhou\n");
        exit(-1);
    }

    if (leftPID == 0) {
        printf("Filho esquerdo. PID: %d, Pai PID: %d\n", getpid(), getppid());
        spawnProcessTree(height + 1, maxHeight);
        fibonacci(30);
        printf("Finalizando trabalho...\n");
        exit(0);
    } 

    pid_t rightPID = fork();
    if (rightPID < 0) {
        fprintf(stderr, "Erro: fork falhou\n");
        exit(-1);
    }
    
    if (rightPID == 0) {
        printf("Filho direito. PID: %d, Pai PID: %d\n", getpid(), getppid());
        spawnProcessTree(height + 1, maxHeight);
        fibonacci(30);
        printf("Finalizando trabalho...\n");
        exit(0);
    } 

    wait(NULL);
    wait(NULL);
}

void spawnProcessChain(int size, int maxSize) {
    if (size > maxSize) { return; }

    pid_t processID = fork();
    if (processID < 0) {
        fprintf(stderr, "Erro: fork falhou\n");
        exit(-1);
    }

    if (processID == 0) {
        spawnProcessChain(size + 1, maxSize);
        printf("Filho. PID: %d, Pai PID: %d\n", getpid(), getppid());
        fibonacci(30);
        printf("Finalizando trabalho...\n");
        exit(0);
    }

    wait(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Erro: numero incorreto de argumentos\n");
        return 1;
    }

    if (!isPositiveInteger(argv[1])) {
        fprintf(stderr, "Erro: o argumento deve ser um número inteiro positivo e não nulo.\n");
        return 1;
    }

    int maxHeight = atoi(argv[1]);
    struct timespec start_t, end_t;
    double total_t;

    if (strcmp(argv[2], "tree") == 0) {
        clock_gettime(CLOCK_REALTIME, &start_t);
        spawnProcessTree(1, maxHeight);
        clock_gettime(CLOCK_REALTIME, &end_t);
    } else if (strcmp(argv[2], "chain") == 0) {
        maxHeight = pow(2, (maxHeight+1)) - 2; // -2, pois o processo inicial é o próprio programa
        clock_gettime(CLOCK_REALTIME, &start_t);
        spawnProcessChain(1, maxHeight);
        clock_gettime(CLOCK_REALTIME, &end_t);
    } else {
        fprintf(stderr, "Erro: tipo de estrutura desconhecida. Use 'tree' ou 'chain'.\n");
        return 1;
    }

    total_t = (end_t.tv_sec - start_t.tv_sec) + (end_t.tv_nsec - start_t.tv_nsec) / 1e9;
    printf("Tempo transcorrido: %f\n", total_t);
    return 0;
}
