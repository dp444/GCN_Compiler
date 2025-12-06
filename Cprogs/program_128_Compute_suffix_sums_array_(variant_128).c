#include <stdio.h>

int main() {
    int a[] = {14,4,3,2,1};
    int n = sizeof(a)/sizeof(a[0]);
    int suf[5];
    int s = 0;
    for (int i = n-1; i >= 0; --i) {
        s += a[i];
        suf[i] = s;
    }
    for (int i = 0; i < n; ++i) printf("%d ", suf[i]);
    printf("\n");
    return 0;
}