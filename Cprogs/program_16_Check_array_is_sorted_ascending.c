#include <stdio.h>

int main() {
    int a[] = {1,2,2,5,8,13};
    int n = sizeof(a)/sizeof(a[0]);
    int sorted = 1;
    for (int i = 1; i < n; ++i)
        if (a[i] < a[i-1]) { sorted = 0; break; }
    printf("Sorted = %d\n", sorted);
    return 0;
}