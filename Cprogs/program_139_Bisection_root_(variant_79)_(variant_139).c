#include <stdio.h>
#include <math.h>

double f(double x){ return x*x - 2; }

double bisection(double a,double b,int iter){
    double m;
    for (int i=0;i<iter;++i){ m=(a+b)/2; if (f(m)==0) break; if (f(a)*f(m) < 0) b=m; else a=m; }
    return m;
}

int main(){ printf("%.12lf\n", bisection(0,2,50)); return 0; }
/* variant */

/* variant */