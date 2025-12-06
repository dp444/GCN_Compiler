#include <stdio.h>

int gcd2(int a, int b) {
    while (b) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    int a = 21, b = 6;
    int g = gcd2(a,b);
    long long l = (long long)a / g * b;
    printf("LCM=%lld\n", l);
    return 0;
}