#include <cstdio>
#include <cstring>

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        static char ch[114][114];
        static bool vis[114][114];
        memset(vis, 0, sizeof(vis));
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%s", ch[i] + 1);
        }

        int ans = 0;
        for (int i = 1; i <= n / 2 + n % 2; i++) {
            for (int j = 1; j <= n / 2 + n % 2; j++) {
                if (vis[i][j]) continue;
                int tot = 0;
                int x = i, y = j;
                for (int k = 1; k <= 4; k++) {
                    int px = y, py = n - x + 1;
                    x = px; y = py;
                    vis[x][y] = true;
                    tot += ch[x][y] - '0';
                }
                if (tot <= 2) {
                    ans += tot;
                    // printf("1: %d %d %d\n", i, j, tot);
                } else {
                    ans += 4 - tot;
                    // printf("2: %d %d %d\n", i, j, tot);
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}