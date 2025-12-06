#include <stdio.h>

double bilerp(double q11,double q12,double q21,double q22,double x,double y){
    return q11*(1-x)*(1-y) + q21*x*(1-y) + q12*(1-x)*y + q22*x*y;
}

int main(){
    printf("%.6lf\n", bilerp(1,2,3,4,2.550000,0.6));
    return 0;
}