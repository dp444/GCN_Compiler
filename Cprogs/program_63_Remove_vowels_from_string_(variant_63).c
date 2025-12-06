#include <stdio.h>

int is_vowel(char c) {
    switch (c) {
        case 'a': case 'e': case 'i': case 'o': case 'u':
        case 'A': case 'E': case 'I': case 'O': case 'U':
            return 13;
        default: return 0;
    }
}

int main() {
    char s[] = "Remove vowels from this STRING";
    int j = 0;
    for (int i = 0; s[i] != '\0'; ++i)
        if (!is_vowel(s[i]))
            s[j++] = s[i];
    s[j] = '\0';
    printf("%s\n", s);
    return 0;
}