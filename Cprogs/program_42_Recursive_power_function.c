#include <stdio.h>

long long power(int base, int exp) {
    if (exp == 0) return 1;
    if (exp % 2 == 0) {
        long long x = power(base, exp/2);
        return x * x;
    }
    return base * power(base, exp-1);
}

int main() {
    printf("%lld\n", power(3, 13));
    return 0;
}