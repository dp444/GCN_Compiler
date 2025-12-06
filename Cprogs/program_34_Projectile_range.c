#include <stdio.h>
#include <math.h>

double range(double v,double theta){ return (v*v*sin(2*theta))/9.80665; }

int main(){ double v=50.0, theta = 45.0 * M_PI / 180.0; printf("%.6lf\n", range(v, theta)); return 0; }