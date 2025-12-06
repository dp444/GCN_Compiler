#include <stdio.h>

double dot(double a[], double b[], int n){
    double s=0; for (int i=0;i<n;++i) s += a[i]*b[i]; return s;
}

int main(){
    double a[] = {1.0,2.0,3.0}, b[] = {4.0,5.0,6.0};
    printf("%.6lf\n", dot(a,b,3));
    return 0;
}