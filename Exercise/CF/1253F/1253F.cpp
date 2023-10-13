// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

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

#define int long long

const int maxn = 1e5 + 10;
int n, m, k, T;
struct Edge {
    int v, w;
};
std::vector<Edge> G[maxn];

void ins(int u, int v, int w) {
    G[u].push_back({v, w});
}

bool vis[maxn];
int dis[maxn];
struct Node {
    int dis, u;
    bool operator < (Node b) const {
        return dis > b.dis;
    }
};
std::priority_queue<Node> q;
void dij() {
    memset(dis, 63, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    dis[0] = 0;
    q.push({0, 0});
    while (!q.empty()) {
        int u = q.top().u; q.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (auto e : G[u]) {
            if (dis[e.v] > dis[u] + e.w) {
                dis[e.v] = dis[u] + e.w;
                q.push({dis[e.v], e.v});
            }
        }
    }
}

int fa[maxn];
int findfa(int u) {
    if (fa[u] == u) return u;
    return fa[u] = findfa(fa[u]);
}
std::vector<std::pair<int, Edge> > Gall;
std::vector<Edge> Gn[maxn];
void kru() {
    for (int i = 0; i <= n; i++) fa[i] = i;
    std::sort(Gall.begin(), Gall.end(), [](auto a, auto b) -> bool {
        return a.second.w < b.second.w;
    });
    for (auto p : Gall) {
        int u = p.first; auto e = p.second;
        // writeln(-1, findfa(u), findfa(e.v));
        if (findfa(u) != findfa(e.v)) {
            // printf("%d %d %d\n", u, e.v, e.w);
            fa[findfa(e.v)] = findfa(u);
            Gn[u].push_back({e.v, e.w});
            Gn[e.v].push_back({u, e.w});
        }
    }
}

int f[maxn][21], ans[maxn][21], dep[maxn];
void dfs(int u, int fa) {
    for (auto e : Gn[u]) {
        if (e.v == fa) continue;
        dep[e.v] = dep[u] + 1;
        f[e.v][0] = u;
        ans[e.v][0] = e.w;
        dfs(e.v, u);
    }
}

void init() {
    for (int i = 1; i <= 20; i++) {
        for (int j = 1; j <= n; j++) {
            f[j][i] = f[f[j][i - 1]][i - 1];
            ans[j][i] = std::max(ans[j][i - 1], ans[f[j][i - 1]][i - 1]);
        }
    }
}

int query(int x, int y) {
    int s = 0;
    if (dep[x] < dep[y]) std::swap(x, y);
    for (int i = 20; i >= 0; i--) {
        if (dep[f[x][i]] < dep[y]) continue;
        s = std::max(s, ans[x][i]);
        // writeln(ans[x][i], x, f[x][i]);
        x = f[x][i];
    }
    if (x == y) return s;
    for (int i = 20; i >= 0; i--) {
        if (f[x][i] == f[y][i]) continue;
        s = std::max(s, std::max(ans[x][i], ans[y][i]));
        // writeln(ans[x][i], ans[y][i]);
        // writeln(x, f[x][i], y, f[y][i]);
        x = f[x][i];
        y = f[y][i];
    }
    s = std::max(s, std::max(ans[x][0], ans[y][0]));
    return s;
}

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, m, k, T);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        read(u, v, w);
        ins(u, v, w); ins(v, u, w);
    }
    for (int i = 1; i <= k; i++) {
        ins(0, i, 0);
    }
    dij();
    // for (int i = 1; i <= n; i++) {
    //     writeln(dis[i]);
    // }

    for (int u = 1; u <= n; u++) {
        for (auto &e : G[u]) {
            e.w = e.w + dis[u] + dis[e.v];
            Gall.push_back({u, e});
        }
    }
    kru();

    dep[1] = 1;
    dfs(1, 1);
    init();


    while (T--) {
        int x, y;
        read(x, y);
        writeln(query(x, y));
    }
    return 0;
}