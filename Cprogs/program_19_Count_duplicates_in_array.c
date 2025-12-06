#include <stdio.h>

int main() {
    int a[] = {1,2,2,3,4,4,4,5};
    int n = sizeof(a)/sizeof(a[0]);
    int dup = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j)
            if (a[i] == a[j]) { ++dup; break; }
    }
    printf("Duplicate values count = %d\n", dup);
    return 0;
}