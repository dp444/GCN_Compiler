#include <stdio.h>

void linreg(double x[], double y[], int n, double *m, double *c){
    double sx=0, sy=0, sxy=0, sxx=0;
    for (int i=0;i<n;++i){ sx+=x[i]; sy+=y[i]; sxy+=x[i]*y[i]; sxx+=x[i]*x[i]; }
    *m = (n*sxy - sx*sy) / (n*sxx - sx*sx);
    *c = (sy - (*m)*sx) / n;
}

int main(){
    double x[] = {1,2,3,4}, y[] = {2,3,5,7};
    double m,c; linreg(x,y,4,&m,&c);
    printf("%.6lf %.6lf\n", m, c);
    return 0;
}
/* variant */

/* variant */