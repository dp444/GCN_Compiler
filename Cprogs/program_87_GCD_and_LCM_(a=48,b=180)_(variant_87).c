#include <stdio.h>

int gcd(int a, int b) {
    while (b) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    int a = 57, b = 180;
    int g = gcd(a,b);
    long l = (long)a / g * b;
    printf("GCD(%d,%d)=%d, LCM=%ld\n", a, b, g, l);
    return 0;
}