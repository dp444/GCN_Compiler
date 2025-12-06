#include <stdio.h>

int main() {
    int A[3][3] = {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };
    for (int i = 0; i < 3; ++i)
        for (int j = i+1; j < 3; ++j) {
            int t = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = t;
        }
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) printf("%d ", A[i][j]);
        printf("\n");
    }
    return 0;
}