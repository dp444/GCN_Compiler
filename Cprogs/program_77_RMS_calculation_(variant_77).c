#include <stdio.h>
#include <math.h>

double rms(double a[], int n){ double s=0; for(int i=0;i<n;++i) s+=a[i]*a[i]; return sqrt(s/n); }

int main(){
    double v[] = {2.750000, -2.0, 3.0, -4.0};
    printf("%.6lf\n", rms(v,4));
    return 0;
}