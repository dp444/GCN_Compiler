#include <stdio.h>

int main() {
    int A[5][3] = {
        {1,0,0},
        {4,5,0},
        {7,8,9}
    };
    int lower = 1;
    for (int i = 0; i < 3; ++i)
        for (int j = i+1; j < 3; ++j)
            if (A[i][j] != 0) lower = 0;
    printf("Lower triangular = %d\n", lower);
    return 0;
}