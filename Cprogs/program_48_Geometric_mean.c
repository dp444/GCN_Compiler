#include <stdio.h>
#include <math.h>

double geo_mean(double a[], int n){ double p=1.0; for(int i=0;i<n;++i) p *= a[i]; return pow(p, 1.0/n); }

int main(){ double a[] = {1.0,3.0,9.0}; printf("%.6lf\n", geo_mean(a,3)); return 0; }