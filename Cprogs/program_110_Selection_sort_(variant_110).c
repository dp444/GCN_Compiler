#include <stdio.h>

int main() {
    int arr[] = {35,10,14,37,13};
    int n = sizeof(arr)/sizeof(arr[0]);
    for (int i=0;i<n-1;++i) {
        int min=i;
        for (int j=i+1;j<n;++j) if (arr[j] < arr[min]) min=j;
        int t = arr[i]; arr[i]=arr[min]; arr[min]=t;
    }
    for (int i=0;i<n;++i) printf("%d ", arr[i]);
    printf("\n");
    return 0;
}