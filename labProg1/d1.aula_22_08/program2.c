#include <stdio.h>

int main() {
    int a = 5, b = 2, c;
    float d;
    
    c = a/b;
    d = (float) a/b;

    printf("%d - %f", c,d);
    
    return 0;
}