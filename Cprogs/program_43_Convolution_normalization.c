#include <stdio.h>

int main(){ double x[] = {0.2,0.2,0.2,0.2,0.2}; double s=0; for (int i=0;i<5;++i) s+=x[i]; for (int i=0;i<5;++i) printf("%.6lf ", x[i]/s); printf("\n"); return 0; }