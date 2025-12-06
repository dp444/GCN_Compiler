#include <stdio.h>
#include <math.h>

double decay(double y0,double k,double t){ return y0 * exp(-k * t); }

int main(){ printf("%.6lf\n", decay(100.0, 0.1, 10.0)); return 0; }