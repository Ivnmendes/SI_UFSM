#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
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
        sleep(20);
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
        sleep(20);
        exit(0);
    } 
    
    printf("Pai. PID: %d, Filhos PID: %d, %d\n", getpid(), leftPID, rightPID);
    wait(NULL);
    wait(NULL);
}

void spawnProcessChain(int size) {
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Erro: numero incorreto de argumentos\n");
        return 1;
    }

    if (!isPositiveInteger(argv[1])) {
        fprintf(stderr, "Erro: o argumento deve ser um número inteiro positivo e não nulo.\n");
        return 1;
    }

    int maxHeight = atoi(argv[1]);

    spawnProcessTree(1, maxHeight);
    return 0;
}
