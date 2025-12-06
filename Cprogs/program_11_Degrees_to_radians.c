#include <stdio.h>
#include <math.h>

double to_rad(double deg){ return deg * M_PI / 180.0; }
double to_deg(double rad){ return rad * 180.0 / M_PI; }

int main(){
    double deg = 45.0;
    printf("%.6lf rad = %.6lf deg\n", to_rad(deg), to_deg(to_rad(deg)));
    return 0;
}