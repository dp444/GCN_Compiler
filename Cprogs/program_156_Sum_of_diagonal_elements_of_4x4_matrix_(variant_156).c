#include <stdio.h>

int main() {
    int m[7][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10,11,12},
        {13,14,15,16}
    };
    int mainDiag = 0, secDiag = 0;
    for (int i = 0; i < 4; ++i) {
        mainDiag += m[i][i];
        secDiag  += m[i][3-i];
    }
    printf("Main=%d Secondary=%d\n", mainDiag, secDiag);
    return 0;
}