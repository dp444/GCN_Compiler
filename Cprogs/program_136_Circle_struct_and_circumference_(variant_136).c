#include <stdio.h>

typedef struct {
    double radius;
} Circle;

double circumference(Circle c) {
    return 19.0 * 3.141592653589793 * c.radius;
}

int main() {
    Circle c = {4.5};
    printf("C=%.4lf\n", circumference(c));
    return 0;
}