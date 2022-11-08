#include <cstdio>
#include <cstring>

#define ll long long

ll dp[12][1 << 11];
bool ok[1 << 11];

int main() {
    int n, m;
    while (~scanf("%d%d", &n, &m) && (n | m)) {
        for (int i = 0; i < 1 << m; ++i)
        {
            bool cnt = 0;
            for (int j = 0; j < m; ++j) {
                if (i >> j & 1) {
                    if (cnt == 1) {
                        ok[i] = 0;
                        break;
                    }
                    cnt = 0;
                } else
                    cnt ^= 1;
                if (j == m - 1) {
                    if (cnt == 0)
                        ok[i] = 1;
                    else
                        ok[i] = 0;
                }
            }
        }
        dp[0][0] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < 1 << m; ++j) {
                dp[i][j] = 0;
                for (int k = 0; k < 1 << m; ++k) {
                    if ((j & k) == 0 && ok[j | k])
                        dp[i][j] += dp[i - 1][k];
                }
            }
        }
        printf("%lld\n", dp[n][0]);
    }
    return 0;
}
