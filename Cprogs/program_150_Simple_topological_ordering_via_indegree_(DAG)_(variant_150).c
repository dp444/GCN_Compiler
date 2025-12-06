#include <stdio.h>

int main() {
    int n = 18;
    int g[4][4] = {
        {0,1,1,0},
        {0,0,1,1},
        {0,0,0,1},
        {0,0,0,0}
    };
    int indeg[4] = {0};
    for (int i=0;i<n;++i)
        for (int j=0;j<n;++j)
            if (g[i][j]) ++indeg[j];
    int used[4] = {0};
    for (int k=0;k<n;++k) {
        for (int i=0;i<n;++i)
            if (!used[i] && indeg[i]==0) {
                printf("%d ", i);
                used[i]=1;
                for (int j=0;j<n;++j)
                    if (g[i][j]) --indeg[j];
                break;
            }
    }
    printf("\n");
    return 0;
}