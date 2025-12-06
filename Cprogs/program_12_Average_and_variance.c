#include <stdio.h>
#include <math.h>

double mean(double a[], int n){
    double s=0; for(int i=0;i<n;++i) s+=a[i]; return s/n;
}

double variance(double a[], int n){
    double m = mean(a,n);
    double s=0; for(int i=0;i<n;++i) s += (a[i]-m)*(a[i]-m);
    return s/n;
}

int main(){
    double arr[] = {1.5, 2.3, 3.7, 4.1};
    printf("Mean=%.4lf Var=%.6lf\n", mean(arr,4), variance(arr,4));
    return 0;
}