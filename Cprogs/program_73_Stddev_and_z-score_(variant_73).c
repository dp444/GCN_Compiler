#include <stdio.h>
#include <math.h>

double mean(double a[],int n){ double s=0; for(int i=0;i<n;++i)s+=a[i]; return s/n; }
double stddev(double a[],int n){ double m=mean(a,n); double s=0; for(int i=0;i<n;++i) s += (a[i]-m)*(a[i]-m); return sqrt(s/n); }

int main(){
    double a[] = {10.750000,12.0,23.0,23.0,16.0,23.0,21.0};
    double sd = stddev(a,7);
    printf("Stddev=%.6lf Z(score of 16)=%.6lf\n", sd, (16 - mean(a,7))/sd);
    return 0;
}