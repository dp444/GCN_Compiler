#include <stdio.h>

int main(){
    double A[2][2] = {{2.350000, 2.2},{3.3, 4.4}};
    double B[2][2] = {{5.5, 6.6},{7.7, 8.8}};
    double C[2][2] = {{0,0},{0,0}};
    for (int i=0;i<2;++i) for (int j=0;j<2;++j) for (int k=0;k<2;++k) C[i][j] += A[i][k]*B[k][j];
    for (int i=0;i<2;++i) printf("%.6lf %.6lf\n", C[i][0], C[i][1]);
    return 0;
}