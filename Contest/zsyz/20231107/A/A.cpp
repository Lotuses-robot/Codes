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

#define int long long
const int maxn = 3e3 + 10, inf = 1e18;
int n, q, s, e0;
int f[maxn][maxn];
int a[maxn], b[maxn], l[maxn], r[maxn];

tsz main() {
    // #ifdef LOCAL
        freopen("A.in", "r", stdin);
        freopen("A.out", "w", stdout);
    // #endif
    
    int T;
    read(T);
    while (T--) {
        read(n, q, s);
        e0 = s - n;
        for (int i = 1; i <= n; i++) {
            read(a[i], b[i], l[i], r[i]);
            l[i] = std::max(0ll, l[i] - e0);
            r[i] = std::max(0ll, r[i] - e0);
            // writeln(l[i], r[i]);
        }
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= 2 * n; j++) {
                f[i][j] = inf;
            }
        f[0][n] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = std::max(l[i], 0ll); j <= std::min(r[i], 2 * n); j++) {
                f[i][j] = std::min(f[i - 1][j - 1] + b[i], f[i - 1][j + 1] + a[i]);
                // writeln(i, j, f[i][j]);
            }
        }
        while (q--) {
            int x, y;
            read(x, y); y -= e0;
            if (y < 0 || y > 2 * n) {
                writeln(-1);
            } else if (f[x][y] >= inf) {
                writeln(-1);
            } else {
                writeln(f[x][y]);
            }
        }
    }
    return 0;
}