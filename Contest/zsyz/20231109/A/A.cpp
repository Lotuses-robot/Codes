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
// #include <algorithm>
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

#define ll long long

const int maxn = 2e5 + 10, mod = 998244353;
int f[maxn];

ll qpow(ll x, int y) {
    ll ans = 1;
    do {
        if (y & 1) ans *= x, ans %= mod;
        x *= x; x %= mod;
    } while (y >>= 1);
    return ans;
}

#define add(x, y) (((x) + (y)) >= (mod - 1) ? ((x) + (y) - (mod - 1)) : ((x) + (y)))

tsz main() {
    // #ifdef LOCAL
    //     freopen(".in", "r", stdin);
    //     freopen(".out", "w", stdout);
    // #endif
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);

    int n; ll ans = 1;
    read(n);
    f[1] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = i * (i - 1) / 2; j >= 1; j--) {
            f[j + i] = add(f[j + i], f[j]);
        }
        f[i] = add(f[i], 1);
    }
    for (int i = 2; i <= n * (n + 1) / 2; i++) {
        ans *= qpow(i, f[i]);
        ans %= mod;
    }
    writeln(ans);
    return 0;
}