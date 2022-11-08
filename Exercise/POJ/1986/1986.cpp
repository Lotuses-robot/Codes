#include <cstdio>
#include <vector>
#include <iostream>

#define int long long

struct Edge {
    int from, to, w;
};

#define sz 1145141
std::vector<Edge> G[sz];

void insert(int u, int v, int w) {
    G[u].push_back({u, v, w});
    G[v].push_back({v, u, w});
}

int fa[sz], dep[sz], siz[sz], son[sz], d[sz];
void dfs1(int u, int Fa) {
    fa[u] = Fa;
    siz[u] = 1;
    if (fa[u] != -1) dep[u] = dep[fa[u]] + 1;
    int mx = -1;
    for (int i = 0; i < G[u].size(); i++) {
        Edge e = G[u][i];
        if (e.to == fa[u]) continue;
        d[e.to] = d[u] + e.w;
        dfs1(e.to, u);
        siz[u] += siz[e.to];
        if (siz[e.to] > mx) {
            mx = siz[e.to];
            son[u] = e.to;
        }
    }
    if (mx == -1) son[u] = -1;
}

int top[sz];
void dfs2(int u, int nowTop) {
    top[u] = nowTop;
    if (son[u] != -1) dfs2(son[u], nowTop);
    for (int i = 0; i < G[u].size(); i++) {
        Edge e = G[u][i];
        if (e.to == fa[u] || e.to == son[u]) continue;
        dfs2(e.to, e.to);
    }
}

int lca(int p1, int p2) {
    while (top[p1] != top[p2]) {
        if (dep[top[p1]] > dep[top[p2]]) std::swap(p1, p2);
        p2 = fa[top[p2]];
    }
    if (dep[p1] > dep[p2]) std::swap(p1, p2);
    return p1;
}

signed main() {
    int n, m;
    scanf("%lld%lld", &n, &m);
    for (int i = 0; i < m; i++) {
        int a, b, c; char ch;
        scanf("%lld%lld%lld", &a, &b, &c);
        std::cin >> ch;
        insert(a, b, c);
    }
    dfs1(1, -1);
    dfs2(1, 1);
    int k;
    scanf("%lld", &k);
    while (k--) {
        int a, b;
        scanf("%lld%lld", &a, &b);
        printf("%lld\n", d[a] + d[b] - 2 * d[lca(a, b)]);
    }
    return 0;
}