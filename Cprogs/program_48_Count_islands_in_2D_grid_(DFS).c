#include <stdio.h>

#define R 3
#define C 4

int grid[R][C] = {
    {1,1,0,0},
    {0,1,0,1},
    {1,0,0,1}
};

void dfs(int r,int c){
    if (r<0||r>=R||c<0||c>=C||grid[r][c]==0) return;
    grid[r][c] = 0;
    dfs(r+1,c); dfs(r-1,c); dfs(r,c+1); dfs(r,c-1);
}

int main(){
    int islands=0;
    for (int i=0;i<R;++i)
        for (int j=0;j<C;++j)
            if (grid[i][j]){
                ++islands;
                dfs(i,j);
            }
    printf("Islands=%d\n", islands);
    return 0;
}