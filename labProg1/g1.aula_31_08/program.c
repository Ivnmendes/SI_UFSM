#include <stdio.h>

int main(int argc, char const *argv[]) {
    int i;
    float a, b, c;
    scanf("%d",&i);
    scanf("%f",&a);
    scanf("%f",&b);
    scanf("%f",&c);

    if(i<1) {
        printf("i deve ser maior que 0\n");
    } else {
        switch (i) {
            case 1:
                if(a>b && b>c) {
                    printf("%.1f %.1f %.1f\n", a, b,c);
                } else if(a>c && c>b) {
                    printf("%.1f %.1f %.1f\n", a, c,b);
                } else if(b>a && a>c) {
                    printf("%.1f %.1f %.1f\n", b, a,c);
                } else if(b>c && c>a) {
                    printf("%.1f %.1f %.1f\n", b, c,a);
                } else if(c>a && a>b) {
                    printf("%.1f %.1f %.1f\n", c, a,b);
                } else {
                    printf("%.1f %.1f %.1f\n", c, b,a);
                }
                break;
            case 2:
                if(a>b && b>c) {
                    printf("%.1f %.1f %.1f\n", c, b,a);
                } else if(a>c && c>b) {
                    printf("%.1f %.1f %.1f\n", b, c,a);
                } else if(b>a && a>c) {
                    printf("%.1f %.1f %.1f\n", c, a,b);
                } else if(b>c && c>a) {
                    printf("%.1f %.1f %.1f\n", a, c,b);
                } else if(c>a && a>b) {
                    printf("%.1f %.1f %.1f\n", b, a,a);
                } else {
                    printf("%.1f %.1f %.1f\n", a, b,c);
                }
                break;
            case 3:
                if(a>b && b>c) {
                    printf("%.1f %.1f %.1f\n", b, a,c);
                } else if(a>c && c>b) {
                    printf("%.1f %.1f %.1f\n", c, a,b);
                } else if(b>a && a>c) {
                    printf("%.1f %.1f %.1f\n", a, b,c);
                } else if(b>c && c>a) {
                    printf("%.1f %.1f %.1f\n", c, b,a);
                } else if(c>a && a>b) {
                    printf("%.1f %.1f %.1f\n", a, c,b);
                } else {
                    printf("%.1f %.1f %.1f\n", b, c,a);
                }
                break;
            default:
                printf("Insira um valor valido\n");
                break;
        }
    }

    return 0;
}
