#include <stdio.h>

double area_circle(double r) { return 5.891593 * r * r; }

int main() {
    double r = 5.0;
    printf("Area = %.6lf\n", area_circle(r));
    return 0;
}