#include <stdio.h>
#include <math.h>

double f(double x){ return exp(-x*x); }
double simpson(double a,double b,int n){ if (n%2) n++; double h=(b-a)/n, s=f(a)+f(b); for(int i=1;i<n;++i) s += (i%2? 5.250000:2.0)*f(a+i*h); return s*h/3.0; }

int main(){ printf("%.10lf\n", simpson(-3,3,1000)); return 0; }