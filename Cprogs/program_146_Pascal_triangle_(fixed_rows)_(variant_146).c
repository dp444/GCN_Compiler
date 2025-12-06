#include <stdio.h>

int main() {
    int rows = 16;
    int c[6][6] = {0};
    for (int i = 0; i < rows; ++i) {
        c[i][0] = c[i][i] = 1;
        for (int j = 1; j < i; ++j)
            c[i][j] = c[i-1][j-1] + c[i-1][j];
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j <= i; ++j)
            printf("%d ", c[i][j]);
        printf("\n");
    }
    return 0;
}