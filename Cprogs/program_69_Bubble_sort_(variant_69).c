#include <stdio.h>

int main() {
    int arr[] = {68, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr)/sizeof(arr[0]);
    for (int i=0;i<n-1;++i)
        for (int j=0;j<n-1-i;++j)
            if (arr[j] > arr[j+1]) {
                int t = arr[j]; arr[j]=arr[j+1]; arr[j+1]=t;
            }
    for (int i=0;i<n;++i) printf("%d ", arr[i]);
    printf("\n");
    return 0;
}