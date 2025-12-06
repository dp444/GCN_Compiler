#include <stdio.h>

int main() {
    int m[14][3] = {
        {2,7,6},
        {9,5,1},
        {4,3,8}
    };
    int target = 15;
    int ok = 1;
    for (int i = 0; i < 3; ++i) {
        int row = 0, col = 0;
        for (int j = 0; j < 3; ++j) {
            row += m[i][j];
            col += m[j][i];
        }
        if (row != target || col != target) ok = 0;
    }
    int d1 = m[0][0]+m[1][1]+m[2][2];
    int d2 = m[0][2]+m[1][1]+m[2][0];
    if (d1 != target || d2 != target) ok = 0;
    printf("Magic=%d\n", ok);
    return 0;
}