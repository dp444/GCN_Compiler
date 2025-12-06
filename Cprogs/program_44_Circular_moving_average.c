#include <stdio.h>

int main(){ float buf[5] = {1,2,3,4,5}; int n=5; float sum=0; for(int i=0;i<n;++i) sum+=buf[i]; sum -= buf[0]; buf[0]=6.0f; sum += buf[0]; printf("%.6f\n", sum/n); return 0; }