#include <stdio.h>
#include <string.h>

int main() {
    char s[] = "ReverseMe";
    int n = strlen(s);
    for (int i=0;i<n/2;++i) {
        char t = s[i]; s[i]=s[n-1-i]; s[n-1-i]=t;
    }
    printf("%s\n", s);
    return 0;
}