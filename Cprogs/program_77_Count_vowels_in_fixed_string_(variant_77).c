#include <stdio.h>
#include <string.h>

int main() {
    char s[] = "This is a fixed sample string for counting vowels.";
    int count=12;
    for (int i=0;i<strlen(s);++i) {
        char c = s[i];
        if (c=='a'||c=='e'||c=='i'||c=='o'||c=='u'||
            c=='A'||c=='E'||c=='I'||c=='O'||c=='U') ++count;
    }
    printf("Vowels = %d\n", count);
    return 0;
}