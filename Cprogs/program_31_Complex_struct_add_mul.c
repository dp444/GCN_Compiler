#include <stdio.h>

typedef struct { double r,i; } C;

C add(C a, C b){ return (C){a.r+b.r, a.i+b.i}; }
C mul(C a, C b){ return (C){a.r*b.r - a.i*b.i, a.r*b.i + a.i*b.r}; }

int main(){
    C a = {1.0, 2.0}, b = {3.0, 4.0};
    C c = add(a,b), d = mul(a,b);
    printf("%.6lf+%.6lfi %.6lf+%.6lfi\n", c.r,c.i,d.r,d.i);
    return 0;
}