#include <cstdio>

int v[114514], c[114514];

int main() {
    freopen("diamond.in", "r", stdin);
    freopen("diamond.out", "w", stdout);
    int n, ans = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &c[i]);
        v[i] -= c[i];
        if (v[i] >= 0) {
            ans += v[i];
        }
    }
    printf("%d\n", ans);
    return 0;
}