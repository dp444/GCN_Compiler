#include <stdio.h>

typedef struct { int x, y; } Point;

Point reflect(Point p) {
    Point r = {-p.x, -p.y};
    return r;
}

int main() {
    Point p = {3, -7};
    Point q = reflect(p);
    printf("(%d,%d)\n", q.x, q.y);
    return 0;
}