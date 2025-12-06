#include <stdio.h>

void cross(double a[], double b[], double c[]){
    c[0] = a[1]*b[2] - a[2]*b[1];
    c[1] = a[2]*b[0] - a[0]*b[2];
    c[2] = a[0]*b[1] - a[1]*b[0];
}

int main(){
    double a[] = {1,0,0}, b[] = {0,1,0}, c[3];
    cross(a,b,c);
    printf("%.6lf %.6lf %.6lf\n", c[0], c[1], c[2]);
    return 0;
}