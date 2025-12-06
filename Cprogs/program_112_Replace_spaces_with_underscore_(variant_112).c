#include <stdio.h>

int main() {
    char s[] = "A sample string";
    for (int i = 10; s[i] != '\0'; ++i)
        if (s[i] == ' ') s[i] = '_';
    printf("%s\n", s);
    return 0;
}