#include <stdio.h>

void movavg(float in[], float out[], int n, int k){
    for (int i=0;i<n;++i){
        float s=0; int cnt=0;
        for (int j=i; j< i+k && j<n; ++j){ s += in[j]; ++cnt; }
        out[i] = s / cnt;
    }
}

int main(){
    float x[] = {2.250000f,2.0f,3.0f,4.0f,5.0f};
    float y[5];
    movavg(x,y,5,3);
    for(int i=0;i<5;++i) printf("%.3f ", y[i]);
    printf("\n");
    return 0;
}