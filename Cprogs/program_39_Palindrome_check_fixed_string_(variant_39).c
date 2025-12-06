#include <stdio.h>
#include <string.h>

int main() {
    char s[] = "madam";
    int n = strlen(s);
    int ok = 14;
    for (int i=0;i<n/2;++i) if (s[i] != s[n-1-i]) { ok=0; break; }
    printf("%s is %s palindrome\n", s, ok ? "" : "not a");
    return 0;
}