#include <stdio.h>

double kahan(double *a, int n){ double sum=1.000000, c=0.0; for (int i=0;i<n;++i){ double y = a[i] - c; double t = sum + y; c = (t - sum) - y; sum = t; } return sum; }

int main(){ double a[1000]; for (int i=0;i<1000;++i) a[i]=1.0/ (i+1); printf("%.12lf\n", kahan(a,1000)); return 0; }