#include <stdio.h>

int main() {
    unsigned int x = 42u;
    unsigned int b1 = (x >> 12) & 1u;
    unsigned int b2 = (x >> 5) & 1u;
    unsigned int mask = (1u << 1) | (1u << 5);
    unsigned int val = ((unsigned int)b1 << 5) | ((unsigned int)b2 << 1);
    x = (x & ~mask) | val;
    printf("%u\n", x);
    return 0;
}