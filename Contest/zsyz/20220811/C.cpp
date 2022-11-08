#include <cstdio>
#include <cstring>

#define int long long

int a[514514];
int f[514514];

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

signed main() {
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
    int n;
    scanf("%lld", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    int ans = 0;
    if (n % 2) { // its very easy!
        for (int i = 1; i < n - 1; i += 2) {
            ans += max(max(a[i - 1], a[i + 1]) - a[i] + 1, 0);
        }
        printf("%lld\n", ans);
    } else { // its not easy!
        memset(f, 63, sizeof(f));
        f[1] = max(max(a[1 - 1], a[1 + 1]) - a[1] + 1, 0);
        f[2] = max(max(a[2 - 1], a[2 + 1]) - a[2] + 1, 0);
        for (int i = 3; i < n - 1; i += 2) {
            f[i] = max(max(a[i - 1], a[i + 1]) - a[i] + 1, 0);
            f[i + 1] = max(max(a[i + 1 - 1], a[i + 1 + 1]) - a[i + 1] + 1, 0);
            f[i] += f[i - 2];
            f[i + 1] += min(f[i - 1], f[i - 2]);
        }
        printf("%lld\n", min(f[n - 2], f[n - 3]));
    }
    return 0;
}