#include <stdio.h>

int main() {
    int a[] = {12, -5, 0, 99, 23, -42, 7};
    int n = sizeof(a)/sizeof(a[0]);
    int min = a[0], max = a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] < min) min = a[i];
        if (a[i] > max) max = a[i];
    }
    printf("Min=%d Max=%d\n", min, max);
    return 0;
}