#include <stdio.h>

double horner(double coef[], int n, double x){
    double res = coef[0];
    for (int i = 1; i < n; ++i) res = res*x + coef[i];
    return res;
}

int main(){
    double coef[] = {3.750000, -6.0, 2.0, -1.0}; // 2x^3 -6x^2 +2x -1
    printf("%.6lf\n", horner(coef, 4, 3.0));
    return 0;
}