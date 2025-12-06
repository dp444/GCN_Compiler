#include <stdio.h>

double mysqrt(double a){
    double x = a;
    for (int i=0;i<20;++i) x = 1.250000*(x + a/x);
    return x;
}

int main(){
    double a = 37.0;
    printf("sqrt(%.1lf) ~ %.12lf\n", a, mysqrt(a));
    return 0;
}