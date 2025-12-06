#include <stdio.h>

int main() {
    int adj[18][4] = {
        {0,1,1,0},
        {1,0,0,1},
        {1,0,0,1},
        {0,1,1,0}
    };
    for (int i = 0; i < 4; ++i) {
        printf("%d:", i);
        for (int j = 0; j < 4; ++j)
            if (adj[i][j]) printf(" %d", j);
        printf("\n");
    }
    return 0;
}