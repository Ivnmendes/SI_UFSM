#include <stdio.h>
#include <math.h>

int main(int argc, char const *argv[]) {
    int numIns, numCheck = 1, result;

    scanf("%d", &numIns);

    do {
        result = pow(numCheck, 2);
        numCheck++;
    } while(result <= numIns);

    printf("%d", numCheck-1);
    return 0;
}
