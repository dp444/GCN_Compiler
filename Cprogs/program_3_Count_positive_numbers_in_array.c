#include <stdio.h>

int main() {
    int a[] = {-3, 5, 7, -1, 0, 4, -2};
    int n = sizeof(a)/sizeof(a[0]);
    int count = 0;
    for (int i = 0; i < n; ++i)
        if (a[i] > 0) ++count;
    printf("Positives = %d\n", count);
    return 0;
}