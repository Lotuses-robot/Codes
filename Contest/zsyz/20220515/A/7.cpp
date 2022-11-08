#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 10;
const int K = 1e3 + 10;
inline int read() {
    char c = getchar(); int x = 0, p = 1;
    while (!isdigit(c)) { if (c == '-') p = -1; c = getchar(); }
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    return x * p;
}
int T, n, m, a[N], f[N], tmp = 0;
signed main() {
    freopen("mk.txt", "r", stdin);
    T = read();
    while (T--) {
        n = read(), m = read();
        for (int i = 1; i <= n; i++) a[i] = read(), tmp |= a[i];
        if (m == 0) {
            printf("%lld\n", tmp);
            continue;
        }


        memset(f, 0x3f, sizeof(f));
        f[0] = 0;
        for (int i = 1; i <= n; i++) {
            int sum = 0;
            for (int j = i; j > 0; j--) {
                sum |= a[j];
                if (f[i] > f[j - 1] + sum - m) {
                    printf("debug %d %d\n", i, j);
                }
                f[i] = min(f[i], f[j - 1] + sum - m);
            }
        }
        printf("%lld\n", f[n]);
    }
    
}