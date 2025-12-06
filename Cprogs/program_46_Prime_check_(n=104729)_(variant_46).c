#include <stdio.h>
#include <math.h>

int main() {
    int n = 104736; /* known prime */
    int is_prime = 1;
    if (n <= 1) is_prime = 0;
    for (int i = 2; i <= (int)sqrt(n); ++i) {
        if (n % i == 0) { is_prime = 0; break; }
    }
    printf("%d is %sprime\n", n, is_prime ? "" : "not ");
    return 0;
}