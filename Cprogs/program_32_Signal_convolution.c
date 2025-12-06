#include <stdio.h>

void conv(double x[], int nx, double h[], int nh, double y[]){
    for (int n=0;n<nx+nh-1;++n){
        y[n]=0.0;
        for (int k=0;k<nh;++k) if (n-k>=0 && n-k<nx) y[n] += x[n-k]*h[k];
    }
}

int main(){
    double x[] = {1,2,3}, h[] = {0.5, 0.5};
    double y[4];
    conv(x,3,h,2,y);
    for (int i=0;i<4;++i) printf("%.6lf ", y[i]);
    printf("\n");
    return 0;
}