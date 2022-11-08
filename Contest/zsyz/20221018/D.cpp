#include <bits/stdc++.h>
#define Mod 100000007
using namespace std;

int n, m, mod;
int a[811][811], ans;
int dp[811][811][18][3];

signed main() {
    // freopen("D.in", "r", stdin);
    // freopen("D.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &mod);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j][a[i][j]][0] = 1; // 0Îª a,·ñÔòÎª uim
            //			printf("dp:%d %d %d\n",i,j,a[i][j]);
            for (int k = 0; k <= mod; k++) {
                int x = (k + a[i][j]) % (mod + 1),
                        y = (k - a[i][j] + mod + 1) % (mod + 1);
                dp[i][j][x][0] += dp[i][j - 1][k][1] + dp[i - 1][j][k][1];
                dp[i][j][x][0] %= Mod;
                dp[i][j][y][1] += dp[i][j - 1][k][0] + dp[i - 1][j][k][0];
                dp[i][j][y][1] %= Mod;
            }
            ans += dp[i][j][0][1];
            ans %= Mod;
        }
    }
    /*
    for(int i=1;i<=n;i++)
    {
                    for(int j=1;j<=m;j++)
                    {
                                    printf("run %d %d:\n",i,j);
                                    for(int k=0;k<=mod;k++)
                                    {
                                                    printf("%d ",dp[i][j][k][0]);
                                    }
                                    puts("");
                                    for(int k=0;k<=mod;k++)
                                    {
                                                    printf("%d ",dp[i][j][k][1]);
                                    }
                                    puts("");
                    }
    }*/
    printf("%lld", ans);
    return 0;
}
