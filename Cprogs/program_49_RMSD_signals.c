#include <stdio.h>
#include <math.h>

double rmsd(double a[], double b[], int n){ double s=0; for (int i=0;i<n;++i){ double d=a[i]-b[i]; s+=d*d; } return sqrt(s/n); }

int main(){ double a[]={1,2,3}, b[]={1.1,1.9,2.95}; printf("%.6lf\n", rmsd(a,b,3)); return 0; }