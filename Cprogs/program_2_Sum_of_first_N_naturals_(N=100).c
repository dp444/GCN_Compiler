#include <stdio.h>

int main() {
    int N = 100;
    long sum = 0;
    for (int i = 1; i <= N; ++i) sum += i;
    printf("Sum of first %d numbers = %ld\n", N, sum);
    return 0;
}