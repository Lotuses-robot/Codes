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

const int maxn = 500005 << 2;
struct Edge {
    int u, v;
};
std::vector<Edge> G[maxn];

int dep[maxn], siz[maxn], son[maxn], fa[maxn];
void dfs1(int u) {
    son[u] = -1; siz[u] = 1;
    for (Edge e : G[u]) {
        if (e.v != fa[u]) {
            fa[e.v] = u;
            dep[e.v] = dep[u] + 1;
            dfs1(e.v);
            siz[u] += siz[e.v];
            if (son[u] == -1 || siz[son[u]] < siz[e.v]) {
                son[u] = e.v;
            }
        }
    }
}

int top[maxn];
void dfs2(int u, int t) {
    top[u] = t;
    if (son[u] == -1) return;
    dfs2(son[u], t);
    for (Edge e : G[u]) {
        if (e.v != fa[u] && e.v != son[u]) {
            dfs2(e.v, e.v);
        }
    }
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        // freopen(".out", "w", stdout);
    #endif
    
    int n, m, s;
    read(n, m, s);
    for (int i = 1; i < n; i++) {
        int x, y;
        read(x, y);
        G[x].push_back({x, y});
        G[y].push_back({y, x});
    }
    dfs1(s);
    dfs2(s, s);
    for (int i = 1; i <= m; i++) {
        int a, b;
        read(a, b);
        while (top[a] != top[b]) {
            if (dep[top[a]] < dep[top[b]]) std::swap(a, b);
            a = fa[top[a]];
            // writeln(a, b);
        }
        if (dep[a] > dep[b]) {
            std::swap(a, b);
        }
        writeln(a);
    }
    return 0;
}
