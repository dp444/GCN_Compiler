#include <stdio.h>

int main(){
    double A[3][4] = {
        {2,1,-1,8},
        {-3,-1,2,-11},
        {-2,1,2,-3}
    };
    int n=3;
    for (int i=0;i<n;++i){
        for (int k=i+1;k<n;++k){
            double c = A[k][i]/A[i][i];
            for (int j=i;j<=n;++j) A[k][j] -= c*A[i][j];
        }
    }
    double x[3];
    for (int i=n-1;i>=0;--i){
        x[i]=A[i][n];
        for (int j=i+1;j<n;++j) x[i] -= A[i][j]*x[j];
        x[i] /= A[i][i];
    }
    printf("%.6lf %.6lf %.6lf\n", x[0], x[1], x[2]);
    return 0;
}
/* variant */