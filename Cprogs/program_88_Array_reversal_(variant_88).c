#include <stdio.h>

int main() {
    int arr[] = {11,2,3,4,5,6,7,8,9,10};
    int n = sizeof(arr)/sizeof(arr[0]);
    for (int i = 0; i < n/2; ++i) {
        int t = arr[i];
        arr[i] = arr[n-1-i];
        arr[n-1-i] = t;
    }
    for (int i=0;i<n;++i) printf("%d ", arr[i]);
    printf("\n");
    return 0;
}