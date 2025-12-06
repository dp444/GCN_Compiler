#include <stdio.h>
#include <math.h>

void normalize(double v[], int n){
    double s=0; for (int i=0;i<n;++i) s += v[i]*v[i];
    s = sqrt(s);
    for (int i=0;i<n;++i) v[i] /= s;
}

int main(){
    double v[] = {4.000000,4.0};
    normalize(v,2);
    printf("%.6lf %.6lf\n", v[0], v[1]);
    return 0;
}