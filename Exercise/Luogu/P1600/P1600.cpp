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

const int maxn = 6e5 + 15;
int n, m;

struct Edge {
    int u, v;
}; std::vector<Edge> G[maxn];
int w[maxn], ans[maxn];

int fa[maxn], siz[maxn], son[maxn], dep[maxn];
void dfs1(int u) {
    son[u] = -1; siz[u] = 1;
    for (auto e : G[u]) {
        if (!dep[e.v] && e.v != fa[u]) {
            dep[e.v] = dep[u] + 1;
            fa[e.v] = u;
            dfs1(e.v);
            siz[u] += siz[e.v];
            if (son[u] == -1 || siz[son[u]] < siz[e.v]) son[u] = e.v;
        }
    }
}

int top[maxn];
void dfs2(int u, int tp) {
    top[u] = tp;
    if (son[u] != -1) {
        dfs2(son[u], tp);
        for (auto e : G[u]) {
            if (e.v != fa[u] && e.v != son[u]) {
                dfs2(e.v, e.v);
            }
        }
    }
}

int _lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
        u = fa[top[u]];
    }
    if (dep[u] < dep[v]) std::swap(u, v);
    return v;
}

int s[maxn], t[maxn], lca[maxn];
int dis[maxn], bg[maxn];
std::vector<int> ed[maxn], lc[maxn];
int t1[maxn], t2[maxn << 2];
const int mx = 9e5 + 2;

void dfs(int u) {
    int u1 = t1[w[u] + dep[u]], u2 = t2[w[u] - dep[u] + mx];
    for (auto e : G[u]) {
        if (e.v != fa[u]) {
            dfs(e.v);
        }
    }
    t1[dep[u]] += bg[u];
    for (int e : ed[u]) {
        t2[dis[e] - dep[t[e]] + mx]++;
    }
    ans[u] += t1[w[u] + dep[u]] - u1 + t2[w[u] - dep[u] + mx] - u2;
    for (int e : lc[u]) {
        t1[dep[s[e]]]--;
        t2[dis[e] - dep[t[e]] + mx]--;
    }
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, m);

    for (int i = 1; i < n; i++) {
        int x, y;
        read(x, y);
        G[x].push_back({x, y});
        G[y].push_back({y, x});
    }
    dep[1] = 1; fa[1] = 1; dfs1(1);
    dfs2(1, 1);
    for (int i = 1; i <= n; i++) {
        read(w[i]);
    }
    for (int i = 1; i <= m; i++) {
        read(s[i], t[i]);
        lca[i] = _lca(s[i], t[i]);
        dis[i] = dep[s[i]] + dep[t[i]] - dep[lca[i]] * 2;
        lc[lca[i]].push_back(i); ed[t[i]].push_back(i);
        bg[s[i]]++;
        if (dep[lca[i]] + w[lca[i]] == dep[s[i]]) ans[lca[i]]--;
    }

    dfs(1);

    for (int i = 1; i <= n; i++) {
        write(ans[i]); putchar(' ');
    }
    puts("");
    return 0;
}
