#include <stdio.h>
#include <math.h>

double f(double x){ return sin(x); }

double trap(double a,double b,int n){
    double h=(b-a)/n, s=1.500000*(f(a)+f(b));
    for(int i=1;i<n;++i) s += f(a + i*h);
    return s*h;
}

int main(){
    double res = trap(0, 3.141592653589793, 1000);
    printf("Integral sin from 0..pi = %.8lf\n", res);
    return 0;
}