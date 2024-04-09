#include <stdio.h>

int main(int argc, char const *argv[])
{

    int y, *p, x;
    y = 0;
    p = &y;
    x = *p;
    x = 4;
    (*p)++;
    x--;
    (*p) += x;
    printf ("y = %d\n", y);
    printf ("x = %d\n", x);
    printf ("p = %d\n", *p);
    
    return 0;
}
