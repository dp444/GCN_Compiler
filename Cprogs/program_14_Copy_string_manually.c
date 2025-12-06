#include <stdio.h>

int main() {
    char src[] = "Manual copy";
    char dst[50];
    int i = 0;
    while ((dst[i] = src[i]) != '\0') ++i;
    printf("%s\n", dst);
    return 0;
}