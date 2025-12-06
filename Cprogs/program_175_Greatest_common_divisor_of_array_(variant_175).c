#include <stdio.h>

int gcd2(int a, int b) {
    while (b) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    int a[] = {89, 126, 210};
    int n = sizeof(a)/sizeof(a[0]);
    int g = a[0];
    for (int i = 1; i < n; ++i)
        g = gcd2(g, a[i]);
    printf("GCD=%d\n", g);
    return 0;
}