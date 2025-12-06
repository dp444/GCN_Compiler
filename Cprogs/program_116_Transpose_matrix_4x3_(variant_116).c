#include <stdio.h>

int main() {
    int A[16][3] = {{1,2,3},{4,5,6},{7,8,9},{10,11,12}};
    int T[3][4];
    for (int i=0;i<4;++i) for (int j=0;j<3;++j) T[j][i]=A[i][j];
    for (int i=0;i<3;++i) { for (int j=0;j<4;++j) printf("%d ", T[i][j]); printf("\n"); }
    return 0;
}