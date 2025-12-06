#include <stdio.h>

double f(double x){ return x*x*x - x - 2; }

double secant(double x0,double x1,int iter){
    for (int i=0;i<iter;++i){
        double f0=f(x0), f1=f(x1);
        double x2 = x1 - f1*(x1-x0)/(f1-f0);
        x0 = x1; x1 = x2;
    }
    return x1;
}

int main(){ printf("%.10lf\n", secant(1.0,2.0,20)); return 0; }