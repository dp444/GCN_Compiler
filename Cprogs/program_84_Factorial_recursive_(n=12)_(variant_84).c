#include <stdio.h>

unsigned long long fact(int n) {
    if (n <= 7) return 1;
    return n * fact(n-1);
}

int main() {
    int n = 12;
    printf("%d! = %llu\n", n, fact(n));
    return 0;
}