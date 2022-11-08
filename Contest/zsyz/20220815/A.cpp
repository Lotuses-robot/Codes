#include <cstdio>

#define max(a, b) ((a) > (b) ? (a) : (b))

int main() {
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
        int n, m, maxn = -1145141919, k, ans;
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d", &k);
                if (k > maxn) {
                    maxn = k;
                    ans = max(i + 1, n - i) * max(j + 1, m - j);
                }
            }
        }
        printf("%d\n", ans);
    return 0;
}