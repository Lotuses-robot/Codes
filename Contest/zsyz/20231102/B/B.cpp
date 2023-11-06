// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
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

const int maxn = 5e3 + 10, mod = 1e9 + 7;
int n, a[maxn], nxt[maxn];
int f[maxn][maxn];

int dfs(int x, int y) {
    if (y > x) return 0;
    if (y == 0) return 1;
    // writeln(x, y, f[x][y]);
    if (~f[x][y]) return f[x][y];
    return f[x][y] = (dfs(nxt[x], y) + dfs(x, y - 1)) % mod;
}

tsz main() {
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
    
    int T;
    read(T);
    while (T--) {
        read(n);
        // memset(f, -1, sizeof(f[0]) * (n + 5));
        for (int i = 0; i <= n + 5; i++) {
            for (int j = 0; j <= n + 5; j++) {
                f[i][j] = -1;
            }
        }
        for (int i = 1; i <= n; i++) {
            read(a[i]);
        }
        std::sort(a + 1, a + n + 1);
        nxt[1] = -1;
        for (int i = 2; i <= n; i++) {
            if (a[i] == a[i - 1]) {
                nxt[i] = nxt[i - 1];
            } else {
                nxt[i] = i - 1;
            }
        }
        for (int k = 1; k <= n; k++) {
            writeln(dfs(n, k));
        }
    }
    return 0;
}