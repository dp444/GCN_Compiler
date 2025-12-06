#include <stdio.h>

double f(double x){ return x*x*x - 2*x -5; }
double df(double x){ return 3*x*x - 2; }

double newton(double x0, int iter){
    for (int i=0;i<iter;++i) x0 -= f(x0)/df(x0);
    return x0;
}

int main(){ printf("%.12lf\n", newton(3.000000,20)); return 0; }