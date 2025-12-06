#include <stdio.h>

int main() {
    int a[] = {10,2,3,4,5};
    int n = sizeof(a)/sizeof(a[0]);
    int pref[5];
    int s = 0;
    for (int i = 0; i < n; ++i) {
        s += a[i];
        pref[i] = s;
    }
    for (int i = 0; i < n; ++i) printf("%d ", pref[i]);
    printf("\n");
    return 0;
}