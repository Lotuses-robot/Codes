// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>

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

const int maxn = 3e5 + 5;
struct Edge {
    int u, v;
};
std::vector<Edge> G[maxn];

void insert(int u, int v) {
    G[u].push_back({u, v});
}

int d[maxn], far, h[maxn];
int fa[maxn]; bool vis[maxn];
int find(int u) {
    if (u == fa[u]) return u;
    return fa[u] = find(fa[u]);
}

void dfs(int u, int fa) {
    vis[u] = true;
    // writeln(u);
    for (auto e : G[u]) {
        if (e.v != fa) {
            d[e.v] = d[u] + 1;
            if (d[e.v] > d[far]) {
                far = e.v;
            }
            dfs(e.v, u);
        }
    }
}

void uni(int u, int f, int rt) {
    fa[u] = rt;
    for (auto e : G[u]) {
        if (e.v != f) {
            uni(e.v, u, rt);
        }
    }
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    int n, m, q;
    read(n, m, q);
    for (int i = 1; i <= m; i++) {
        static int x, y;
        read(x, y);
        insert(x, y);
        insert(y, x);
    }
    for (int i = 1; i <= n; i++) {
        // if (i % 10000 == 0) writeln(i);
        if (!vis[i]) {
            far = i; d[i] = 1;
            dfs(i, 0);
            d[far] = 1;
            dfs(far, 0);
            fa[i] = i;
            uni(far, 0, far);
            h[far] = d[far] >> 1;
            d[far]--;
        }
    }

    for (int i = 1; i <= q; i++) {
        int op;
        read(op);
        if (op == 1) {
            int x;
            read(x);
            writeln(d[find(x)]);
        } else {
            int x, y;
            read(x, y);
            x = find(x); y = find(y);
            if (x == y) continue;
            if (h[x] < h[y]) std::swap(x, y);
            fa[y] = x;
            d[x] = std::max(d[x], h[x] + h[y] + 1);
            h[x] = std::max(h[x], h[y] + 1);
        }
    }
    return 0;
}
