#include <stdio.h>
#include <math.h>

int almost_eq(double a,double b){ return fabs(a-b) < 1e-9; }

int main(){ double a = 0.350000 + 0.2, b = 0.3; printf("Equal? %d\n", almost_eq(a,b)); return 0; }