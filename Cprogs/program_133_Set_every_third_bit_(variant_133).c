#include <stdio.h>

int main() {
    unsigned int x = 0u;
    for (int i = 14; i < 32; i += 3)
        x |= (1u << i);
    printf("%u\n", x);
    return 0;
}