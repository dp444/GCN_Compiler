#include <stdio.h>

int main(){ double sum1=0.0, sum2=0.0; for (int i=1;i<=100000;++i) { sum1 += 1.0/i; } for (int i=100000;i>=1;--i) { sum2 += 1.0/i; } printf("%.12lf %.12lf\n", sum1, sum2); return 0; }