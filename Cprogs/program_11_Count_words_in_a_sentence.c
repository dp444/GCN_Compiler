#include <stdio.h>

int main() {
    char s[] = "Count the number of words here";
    int words = 0;
    int in_word = 0;
    for (int i = 0; s[i] != '\0'; ++i) {
        if (s[i] != ' ' && !in_word) {
            in_word = 1;
            ++words;
        } else if (s[i] == ' ') {
            in_word = 0;
        }
    }
    printf("Words = %d\n", words);
    return 0;
}