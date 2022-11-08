#include <cstdio>
#include <cmath>
#define int long long

#define min(a, b) ((a) < (b) ? (a) : (b))
#define mod 998244353

signed main() {
    int n, m, k;
    static int f[100][30000];
    scanf("%lld%lld%lld", &n, &m, &k);

    for (int p = k - m; p < k; p++) {
        f[0][p] = 1;
    }

    for (int i = 1; i < n; i++) {
        for (int p = 0; p <= k; p++) {
            for (int j = 1; j <= m; j++) {
                if (p + j > k) {
                    continue;
                }
                f[i][p] += f[i - 1][p + j];
                f[i][p] %= mod;
            }
        }
    }
    
    int ans = 0;

    for (int p = 0; p <= k; p++) {
        ans += f[n - 1][p];
        ans %= mod;
    }
    printf("%lld", ans);
    return 0;
}