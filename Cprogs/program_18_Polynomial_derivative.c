#include <stdio.h>

void derivative(double coef[], int n, double out[]){
    for (int i=0;i<n-1;++i) out[i] = coef[i]*(n-1-i);
}

int main(){
    double coef[] = {3.0, 2.0, -1.0}; // 3x^2 + 2x -1
    double der[2];
    derivative(coef, 3, der);
    printf("%.3lf %.3lf\n", der[0], der[1]);
    return 0;
}