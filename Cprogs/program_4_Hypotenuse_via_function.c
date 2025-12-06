#include <stdio.h>
#include <math.h>

double hyp(double a, double b) { return sqrt(a*a + b*b); }

int main() {
    double a = 3.0, b = 4.0;
    printf("Hypotenuse = %.2lf\n", hyp(a,b));
    return 0;
}