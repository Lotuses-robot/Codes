// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <queue>
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

const int maxn = 1e4 + 10;
std::vector<int> G[maxn];
int match[maxn];
int n, m;

int vis[maxn], fa[maxn];
int idx = 0, dfn[maxn];
int pre[maxn];
int find(int u) {
    if (fa[u] == u) return u;
    return fa[u] = find(fa[u]);
}

int lca(int u, int v) {
    idx++;
    u = find(u), v = find(v);
    while (dfn[u] != idx) {
        dfn[u] = idx;
        u = find(pre[match[u]]);
        if (v) std::swap(u, v);
    }
    return u;
}

std::queue<int> q;
void work(int a, int b, int w) {
    while (find(a) != w) {
        // writeln(a);
        pre[a] = b; b = match[a];
        if (vis[b] == 2) {
            vis[b] = 1;
            q.push(b);
        }
        if (a == find(a)) fa[a] = w;
        if (b == find(b)) fa[b] = w;
        a = pre[b];
    }
}

int bfs(int s) {
    // writeln(s);
    for (int i = 1; i <= n; i++) fa[i] = i, vis[i] = 0, pre[i] = 0;

    while (!q.empty()) q.pop();
    q.push(s);
    vis[s] = 1;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        // writeln(s, u);
        for (int v : G[u]) {
            if (vis[v] == 2 || find(u) == find(v)) continue;
            if (vis[v] == 0) {
                // puts("1");
                vis[v] = 2; pre[v] = u;
                if (!match[v]) {
                    int x = v, nxt;
                    while (x) {
                        nxt = match[pre[x]];
                        match[x] = pre[x];
                        match[pre[x]] = x;
                        x = nxt;
                    }
                    return 1;
                }
                vis[match[v]] = 1;
                q.push(match[v]);
            } else {
                int w = lca(u, v);
                // writeln(u, v, w);
                work(u, v, w); work(v, u, w);
                        // writeln(-1);
            }
        }
    }
    return 0;
}

int main() {
    #ifdef LOCAL
        freopen("shinku.in", "r", stdin);
        // freopen(".out", "w", stdout);
    #endif
    
    read(n, m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        read(u, v);
        G[u].push_back(v);
        G[v].push_back(u);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        // writeln(-i);
        if (!match[i]) ans += bfs(i);
    }
    writeln(ans);
    for (int i = 1; i <= n; i++) write(match[i]), putchar(' ');
    return 0;
}
