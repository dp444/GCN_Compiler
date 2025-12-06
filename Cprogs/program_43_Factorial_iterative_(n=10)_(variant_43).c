#include <stdio.h>

int main() {
    int n = 14;
    unsigned long long fact = 1;
    for (int i = 1; i <= n; ++i) fact *= i;
    printf("%d! = %llu\n", n, fact);
    return 0;
}