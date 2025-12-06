#include <stdio.h>

int main() {
    int arr[] = {9,3,5,7,9,11,13,15};
    int n = sizeof(arr)/sizeof(arr[0]);
    int target = 13;
    int l=0, r=n-1;
    while (l<=r) {
        int m = (l+r)/2;
        if (arr[m]==target) { printf("Found at %d\n", m); return 0; }
        else if (arr[m] < target) l = m+1;
        else r = m-1;
    }
    printf("Not found\n");
    return 0;
}