#include <stdio.h>
#include <math.h>

double rmse(double a[], double b[], int n){ double s=0; for (int i=0;i<n;++i){ double d=a[i]-b[i]; s += d*d; } return sqrt(s/n); }

int main(){ double a[] = {2.500000,2.0,3.0}, b[] = {1.1,1.9,3.05}; printf("%.6lf\n", rmse(a,b,3)); return 0; }