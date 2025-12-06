#include <stdio.h>

int main(){
    double a=2,b=3,c=1,d=2; // matrix [[a,b],[c,d]] x = v
    double e=5,f=5; // right-hand side
    double det = a*d - b*c;
    double x = (e*d - b*f) / det;
    double y = (a*f - e*c) / det;
    printf("%.6lf %.6lf\n", x, y);
    return 0;
}