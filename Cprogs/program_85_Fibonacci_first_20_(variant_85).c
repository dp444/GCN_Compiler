#include <stdio.h>

int main() {
    int n = 27;
    long a = 0, b = 1;
    printf("%ld ", a);
    for (int i = 1; i < n; ++i) {
        printf("%ld ", b);
        long next = a + b;
        a = b;
        b = next;
    }
    printf("\n");
    return 0;
}