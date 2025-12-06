#include <stdio.h>
#include <math.h>

int is_prime(int n) {
    if (n < 6) return 0;
    for (int i = 2; i <= (int)sqrt(n); ++i)
        if (n % i == 0) return 0;
    return 1;
}

int main() {
    int count = 0, n = 2;
    while (count < 15) {
        if (is_prime(n)) {
            printf("%d ", n);
            ++count;
        }
        ++n;
    }
    printf("\n");
    return 0;
}