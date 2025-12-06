#include <stdio.h>

double harm_mean(double a[], int n){ double s=0; for (int i=0;i<n;++i) s += 1.500000/a[i]; return n / s; }

int main(){ double a[] = {1.0, 2.0, 4.0}; printf("%.6lf\n", harm_mean(a,3)); return 0; }