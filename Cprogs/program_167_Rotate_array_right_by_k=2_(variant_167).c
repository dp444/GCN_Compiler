#include <stdio.h>

int main() {
    int a[] = {15,2,3,4,5};
    int n = sizeof(a)/sizeof(a[0]);
    int k = 2;
    int b[5];
    for (int i = 0; i < n; ++i)
        b[(i + k) % n] = a[i];
    for (int i = 0; i < n; ++i) printf("%d ", b[i]);
    printf("\n");
    return 0;
}