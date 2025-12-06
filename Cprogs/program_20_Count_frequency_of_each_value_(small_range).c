#include <stdio.h>

int main() {
    int a[] = {0,3,1,2,3,1,0,2,2};
    int n = sizeof(a)/sizeof(a[0]);
    int freq[4] = {0};
    for (int i = 0; i < n; ++i)
        ++freq[a[i]];
    for (int v = 0; v < 4; ++v)
        printf("%d -> %d\n", v, freq[v]);
    return 0;
}