// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

#define gc getchar()
template<typename T>
void read(T &r) { // NOLINT
    r = 0; static char ch, last; // NOLINT
    ch = gc, last = 'z';
    while (ch < '0' || ch > '9') last = ch, ch = gc;
    while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
    r = (last == '-') ? -r : r;
}

template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) { // NOLINT
    read(arg);
    read(arg_left...);
}

struct Edge {
    int from, to;
};
std::vector<Edge> G[114514];
int dis[5500][5500];
bool vis[5500];
std::queue<int> q;

#define min(a, b) ((a) < (b) ? (a) : (b))

void bfs(int s) {
    memset(dis[s], 63, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    q.push(s);

    while (!q.empty()) {
        int p = q.front(); q.pop();
        for (Edge e : G[p]) {
            dis[s][e.to] = min(dis[s][e.to], dis[s][e.from] + 1);
            if (!vis[e.to]) q.push(e.to), vis[e.to] = true;
        }
    }
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    int n, m;
    read(n, m);
    for (int i = 0; i < m; i++) {
        int u, v;
        read(u, v);
        G[u].push_back({u, v});
        G[v].push_back({v, u});
    }

    for (int i = 0; i < n; i++) {
        bfs(i);
    }
}
