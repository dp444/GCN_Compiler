#include <stdio.h>
#include <math.h>

double f(double x){ return cos(x); }

double simpson(double a,double b,int n){
    if(n%2) n++;
    double h = (b-a)/n, s = f(a)+f(b);
    for(int i=1;i<n;++i) s += (i%2? 4.0:2.0)*f(a+i*h);
    return s*h/3.0;
}

int main(){
    printf("%.8lf\n", simpson(0, 3.141592653589793, 100));
    return 0;
}