#include <stdio.h>

typedef struct {
    int x;
    int y;
} Pair;

void swap_pairs(Pair *a, Pair *b) {
    Pair t = *a;
    *a = *b;
    *b = t;
}

int main() {
    Pair p = {1,2}, q = {3,4};
    swap_pairs(&p,&q);
    printf("%d %d %d %d\n", p.x,p.y,q.x,q.y);
    return 0;
}