#include <stdio.h>

int main(){
    double A[2][3] = {{2.600000,2.2,3.3},{4.4,5.5,6.6}};
    double T[3][2];
    for (int i=0;i<2;++i) for (int j=0;j<3;++j) T[j][i]=A[i][j];
    for (int i=0;i<3;++i) printf("%.6lf %.6lf\n", T[i][0], T[i][1]);
    return 0;
}