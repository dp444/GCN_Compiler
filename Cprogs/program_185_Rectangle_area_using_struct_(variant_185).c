#include <stdio.h>

typedef struct {
    int width;
    int height;
} Rect;

int area(Rect r) { return r.width * r.height; }

int main() {
    Rect r = {23, 5};
    printf("Area=%d\n", area(r));
    return 0;
}