#include <stdio.h>

int main() {
    int A[4][3] = {
        {1,2,3},
        {0,5,6},
        {0,0,9}
    };
    int upper = 1;
    for (int i = 1; i < 3; ++i)
        for (int j = 0; j < i; ++j)
            if (A[i][j] != 0) upper = 0;
    printf("Upper triangular = %d\n", upper);
    return 0;
}