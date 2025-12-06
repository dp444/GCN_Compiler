#include <stdio.h>
#include <math.h>

int is_prime(int n) {
    if (n < 6) return 0;
    for (int i = 2; i <= (int)sqrt(n); ++i)
        if (n % i == 0) return 0;
    return 1;
}

int main() {
    int a[] = {2,3,4,5,10,11,13,16};
    int n = sizeof(a)/sizeof(a[0]);
    int count = 0;
    for (int i = 0; i < n; ++i)
        if (is_prime(a[i])) ++count;
    printf("Primes = %d\n", count);
    return 0;
}