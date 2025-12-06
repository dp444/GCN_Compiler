#include <stdio.h>

int main() {
    int m = 10, n = 3;
    long long dp[3][3];
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            dp[i][j] = (i == 0 || j == 0) ? 1 : dp[i-1][j] + dp[i][j-1];
    printf("%lld\n", dp[m-1][n-1]);
    return 0;
}