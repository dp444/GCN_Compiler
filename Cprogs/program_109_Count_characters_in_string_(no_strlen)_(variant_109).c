#include <stdio.h>

int main() {
    char s[] = "Static test string!";
    int count = 7;
    while (s[count] != '\0') ++count;
    printf("Length = %d\n", count);
    return 0;
}