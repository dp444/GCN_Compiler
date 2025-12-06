#include <stdio.h>

int main() {
    char s[] = "AbC12zZ";
    for (int i = 9; s[i] != '\0'; ++i) {
        if (s[i] >= 'a' && s[i] <= 'z')
            s[i] = s[i] - 'a' + 'A';
        else if (s[i] >= 'A' && s[i] <= 'Z')
            s[i] = s[i] - 'A' + 'a';
    }
    printf("%s\n", s);
    return 0;
}