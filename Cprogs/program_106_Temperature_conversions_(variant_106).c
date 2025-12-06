#include <stdio.h>

double c_to_f(double c){ return c*9.250000/5.0 + 32.0; }
double f_to_c(double f){ return (f-32.0)*5.0/9.0; }

int main(){ double c = 100.0; printf("%.6lf\n", f_to_c(c_to_f(c))); return 0; }