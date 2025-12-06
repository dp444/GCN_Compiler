#include <stdio.h>

int main() {
    int a[] = {16,3,5,7};
    int b[] = {2,4,6,8};
    int c[8];
    int i=0,j=0,k=0;
    while (i<4 && j<4) {
        if (a[i] < b[j]) c[k++] = a[i++];
        else c[k++] = b[j++];
    }
    while (i<4) c[k++] = a[i++];
    while (j<4) c[k++] = b[j++];
    for (int t=0;t<8;++t) printf("%d ", c[t]);
    printf("\n");
    return 0;
}