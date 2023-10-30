// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <vector>
// #include <map>
// #include <set>
// #include <list>
// #include <queue>
// #include <stack>
// #include <string>
#include <algorithm>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

template<typename T>
void read(T &r) { r = 0; static char ch, last; ch = getchar(), last = 'z'; while (ch < '0' || ch > '9') last = ch, ch = getchar(); while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = getchar(); r = (last == '-') ? -r : r; }
template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) { read(arg); read(arg_left...); }

template<typename T>
void write(T x) { if (x < 0) putchar('-'), x = -x; int len = 0; static char ch[100]; while (x) ch[++len] = x % 10 + '0', x /= 10; if (!len) ch[++len] = '0'; while (len) putchar(ch[len--]); }
template<typename T, typename...Ts>
void write(T arg, Ts...arg_left) { write(arg); putchar(' '); write(arg_left...); }
template<typename T>
void writeln(T x) { write(x); putchar('\n'); }
template<typename T, typename...Ts>
void writeln(T arg, Ts...arg_left) { write(arg); putchar(' '); write(arg_left...); putchar('\n'); }

// #define __DEBUG
#ifdef __DEBUG
#define debug(arg, args...) { printf("db <%d> ", __LINE__); writeln(arg, ##args); }
#else
#define debug(arg, args...) {}
#endif
#define ins(a, b) (G[a].emplace_back(b))

#define int long long

const int maxn = 1e5 + 10, mod = 998244353;
bool b[maxn];
int p[maxn], phi[maxn], f[maxn];

int qpow(int x, int y) {
    int ans = 1;
    do {
        if (y & 1) ans *= x, ans %= mod;
        x *= x; x %= mod;
    } while (y >>= 1);
    return ans;
}

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    int n = 1e5, tot = 0;

    phi[1] = 1;
    b[0] = b[1] = 1;
    f[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!b[i]) {
            p[++tot] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= tot && i * p[j] <= n; j++) {
            b[i * p[j]] = 1;
            if (i % p[j] == 0) {
                phi[i * p[j]] = phi[i] * p[j] % mod;
                break;
            }
            phi[i * p[j]] = phi[i] * (p[j] - 1) % mod;
        }
        f[i] = f[i - 1] + phi[i] * 2;
        f[i] %= mod;
    }

    int T, k;
    read(T);
    while (T--) {
        read(n, k);
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            ans += qpow((qpow(2, i) - 1), k) * f[n / i] % mod;
            ans %= mod;
        }
        writeln(ans);
    }
    return 0;
}