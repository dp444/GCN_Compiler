#include <stdio.h>

int main() {
    int n = 27;
    long long prod = 1;
    for (int i = 1; i <= n; ++i) prod *= i;
    printf("Product = %lld\n", prod);
    return 0;
}