#include <stdio.h>

int main() {
    unsigned int n = 123464;
    int count = 0;
    while (n) { count += n & 1; n >>= 1; }
    printf("Set bits = %d\n", count);
    return 0;
}