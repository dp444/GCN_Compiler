#include <stdio.h>

double lerp(double a,double b,double t){ return a + (b-a)*t; }

int main(){
    printf("%.6lf\n", lerp(10.0, 20.0, 0.25));
    return 0;
}