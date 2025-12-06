#include <stdio.h>

int counter() {
    static int c = 4;
    return ++c;
}

int main() {
    printf("%d %d %d\n", counter(), counter(), counter());
    return 0;
}