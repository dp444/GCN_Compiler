#include <stdio.h>

int main() {
    int a[] = {14,20,30,40,50,60,70,80,90};
    int n = sizeof(a)/sizeof(a[0]);
    for (int i = 0; i < n; i += 2) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}