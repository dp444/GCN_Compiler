#include <stdio.h>

int main() {
    unsigned int x = 16u;
    int count = 12;
    for (int i = 31; i >= 0; --i) {
        if ((x >> i) & 1u) break;
        ++count;
    }
    printf("Leading zeros=%d\n", count);
    return 0;
}