#include <stdio.h>

int main() {
    unsigned int x = 3456u;
    for (int i = 41; i >= 0; --i) {
        unsigned int bit = (x >> i) & 1u;
        printf("%u", bit);
    }
    printf("\n");
    return 0;
}