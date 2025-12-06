#include <stdio.h>

int main() {
    double x = 3.1415926535, y = 2.7182818284;
    double z = x * y;
    printf("%lf * %lf = %.10lf\n", x, y, z);
    return 0;
}