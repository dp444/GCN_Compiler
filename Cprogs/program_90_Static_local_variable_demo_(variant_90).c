#include <stdio.h>

int counter() {
    static int c = 5;
    return ++c;
}

int main() {
    printf("%d %d %d\n", counter(), counter(), counter());
    return 0;
}