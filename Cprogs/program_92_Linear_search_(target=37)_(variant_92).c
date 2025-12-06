#include <stdio.h>

int main() {
    int arr[] = {6,12,37,9,0,23};
    int n = sizeof(arr)/sizeof(arr[0]);
    int target=37;
    int idx=-1;
    for (int i=0;i<n;++i) if (arr[i]==target) { idx=i; break; }
    if (idx>=0) printf("Found at index %d\n", idx); else printf("Not found\n");
    return 0;
}