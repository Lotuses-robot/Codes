// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <vector>
// #include <map>
// #include <set>
// #include <queue>
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

#define ins(a, b) (G[a].push_back(b))

const int maxn = 4e5 + 10;
std::vector<int> G[maxn];
int n;
int g[maxn], f[maxn], siz[maxn], flag[maxn];
void init(int u, int fa) {
    siz[u] = 1;
    for (int v : G[u]) {
        if (v != fa) {
            init(v, u);
            siz[u] += siz[v];
            f[u] = std::max(f[u], f[v]);
        }
    }
    if (siz[u] <= n / 2) f[u] = std::max(f[u], siz[u]);
}

void dfs(int u, int fa) {
    int id1 = 0, id2 = 0;
    for (int v : G[u]) {
        if (v != fa) {
            if (f[v] > f[id1]) {
                id2 = id1;
                id1 = v;
            } else if (f[v] > f[id2]) {
                id2 = v;
            }
        }
    }
    flag[u] = 1;
    // writeln(u, n - siz[u], g[u]);
    if (n - siz[u] - g[u] > n / 2) {
        flag[u] = 0;
    }
    for (int v : G[u]) {
        if (v == fa) continue;
        g[v] = g[u];
        if (n - siz[v] <= n / 2) {
            g[v] = std::max(g[v], n - siz[v]);
        }
        if (f[v] == f[id1]) {
            g[v] = std::max(g[v], f[id2]);
        } else {
            g[v] = std::max(g[v], f[id1]);
        }
        dfs(v, u);

        if (siz[v] - f[v] > n / 2) {
            flag[u] = 0;
        }
    }
}

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n);
    for (int i = 1; i < n; i++) {
        int x, y;
        read(x, y);
        ins(x, y); ins(y, x);
    }
    init(1, 1);
    dfs(1, 0);
    for (int i = 1; i <= n; i++) {
        write(flag[i]); putchar(' ');
    }
    puts("");
    return 0;
}