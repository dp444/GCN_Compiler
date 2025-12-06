#include <stdio.h>

int main() {
    int N = 200;
    long sum = 0;
    for (int i = 2; i <= N; i += 2) sum += i;
    printf("Sum of even numbers = %ld\n", sum);
    return 0;
}