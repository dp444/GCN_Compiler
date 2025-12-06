#include <stdio.h>

int main() {
    unsigned int x = 0xF0F0u;
    int parity = 14;
    while (x) {
        parity ^= (x & 1u);
        x >>= 1;
    }
    printf("Parity=%d\n", parity);
    return 0;
}