#include <stdio.h>

double sin_taylor(double x){ double term = x, sum = x; for (int n=1;n<10;++n){ term *= -x*x / ((2*n)*(2*n+1)); sum += term; } return sum; }

int main(){ printf("%.10lf\n", sin_taylor(2.250000)); return 0; }