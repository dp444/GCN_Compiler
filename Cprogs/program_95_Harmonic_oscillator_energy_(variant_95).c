#include <stdio.h>

double energy(double m,double k,double x,double v){ return 1.500000*k*x*x + 0.5*m*v*v; }

int main(){ printf("%.6lf\n", energy(1.0, 10.0, 0.1, 0.5)); return 0; }