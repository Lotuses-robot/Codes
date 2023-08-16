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

const int maxn = 2e5 + 10;
std::vector<int> G[maxn];

int son[maxn], fa[maxn], dep[maxn], siz[maxn];
void dfs1(int u) {
    son[u] = -1; siz[u] = 1;
    for (int v : G[u]) {
        if (v != fa[u]) {
            fa[v] = u;
            dep[v] = dep[u] + 1;
            dfs1(v);
            siz[u] += siz[v];
            if (son[u] == -1 || siz[son[u]] < siz[v]) {
                son[u] = v;
            }
        }
    }
}

int top[maxn];
void dfs2(int u, int tp) {
    top[u] = tp;
    if (son[u] == -1) return;
    dfs2(son[u], tp);
    for (int v : G[u]) {
        if (v != son[u] && v != fa[u]) {
            dfs2(v, v);
        }
    }
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) std::swap(u, v);
    return u;
}

int dis[maxn], maxid = -1;
void dfs3(int u, int fa) {
    if (maxid == -1 || dis[u] > dis[maxid]) {
        maxid = u;
    }
    for (int v : G[u]) {
        if (v != fa) {
            dis[v] = dis[u] + 1;
            dfs3(v, u);
        }
    }
}

int l, r;
int faf[maxn][20];
void init(int u) {
    faf[u][0] = fa[u];
    for (int i = 1; i <= 19; i++) {
        faf[u][i] = faf[faf[u][i - 1]][i - 1];
    }
    for (int v : G[u]) {
        if (v != fa[u]) init(v);
    }
}

int findfa(int u, int k) {
    int q = 0;
    do {
        if (k & 1) {
            u = faf[u][q];
        }
        q++;
    } while (k >>= 1);
    return u;
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    int n, u, v;
    read(n);
    for (int i = 1; i < n; i++) {
        read(u, v);
        G[u].push_back(v);
        G[v].push_back(u);
    }

    fa[1] = 1; dep[1] = 0;
    dfs1(1);
    dfs2(1, 1);
    dis[1] = 0; dfs3(1, 1);
    l = maxid; maxid = -1; dis[l] = 0;
    dfs3(l, l); r = maxid;
    dis[1] = 0; dfs3(1, 1);
    init(1);

    int q, k;
    read(q);
    while (q--) {
        read(u, k);
        // l
        int lc = lca(u, l);
        int d = dis[u] + dis[l] - 2 * dis[lc];
        // writeln(666, d, l);
        if (k <= d) {
            if (k <= dis[u]) {
                write(findfa(u, k));
            } else {
                write(findfa(l, d - k));
            }
            goto ed;
        }

        lc = lca(u, r);
        d = dis[u] + dis[r] - 2 * dis[lc];
        // writeln(666, d, r);
        if (k <= d) {
            if (k <= dis[u]) {
                write(findfa(u, k));
            } else {
                write(findfa(r, d - k));
            }
            goto ed;
        }

        write(-1);
        ed: puts("");
    }
    return 0;
}
