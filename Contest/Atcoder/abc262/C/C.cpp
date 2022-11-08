#include <cstdio>

int main() {
    static int a[514514];
    int n, tot = 0;
    long long ans = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        if (a[i] == i) tot++, a[i] = -1;
    }
    for (int i = 1; i <= n; i++) {
        if (a[i] != -1) {
            if (a[a[i]] == i) {
                ans++;
                a[a[i]] = -1;
                a[i] = -1;
            }
        }
    }
    ans += 1ll * tot * (tot - 1) / 2;
    printf("%lld\n", ans);
    return 0;
}