#include <stdio.h>
#include <math.h>

double derivative(double (*f)(double), double x){
    double h = 1e-6;
    return (f(x + h) - f(x - h)) / (2*h);
}

int main(){
    double d = derivative(sin, 3.250000);
    printf("d/dx sin(x) at x=1 ~ %.8lf\n", d);
    return 0;
}