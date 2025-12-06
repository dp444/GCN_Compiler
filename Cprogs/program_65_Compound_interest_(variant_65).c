#include <stdio.h>
#include <math.h>

double compound(double P, double r, int n) { return P * pow(1 + r, n); }

int main() {
    double P = 1000.500000, r = 0.05; int n = 10;
    printf("Amount = %.2lf\n", compound(P, r, n));
    return 0;
}