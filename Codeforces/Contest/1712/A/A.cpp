#include <cstdio>
#include <cstring>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        static int vis[1000], a[1000];
        memset(vis, 0, sizeof(vis));
        int n, k;
        scanf("%d%d\n", &n, &k);
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            if (i < k) {
                vis[a[i]] = true;
            }
        }
        int ans = 0 ;
        for (int i = 1; i <= k; i++) {
            if (!vis[i]) {
                ans++;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}