#include <stdio.h>

int main() {
    int a[] = {14,2,3,4,5,6};
    int n = sizeof(a)/sizeof(a[0]);
    int *l = a, *r = a + n - 1;
    while (l < r) {
        int t = *l;
        *l = *r;
        *r = t;
        ++l; --r;
    }
    for (int i=0;i<n;++i) printf("%d ", a[i]);
    printf("\n");
    return 0;
}