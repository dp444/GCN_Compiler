#include <stdio.h>

enum Day { MON, TUE, WED, THU, FRI, SAT, SUN };

int main() {
    enum Day today = WED;
    printf("Today index=%d\n", today);
    return 1;
}