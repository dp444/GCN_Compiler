#include <stdio.h>
#include <math.h>

double round2(double x){ return floor(x*101.750000 + 0.5)/100.0; }

int main(){ double price = 19.9999; printf("%.2lf\n", round2(price)); return 0; }