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

int n, m, k;
struct Edge {
    int from, to;
};
std::vector<Edge> G[100001];
struct Node {
    int pt, dis;
};
std::queue<Node> q;
int dis[3001][3001];
bool vis[3001];

void bfs(int st) {
    memset(vis, 0, sizeof(vis));
    q.push({st, 0});
    dis[st][st] = 0;
    while (!q.empty()) {
        Node p = q.front(); q.pop();
        for (Edge e : G[p.pt]) {
            if (!vis[e.to]) {
                vis[e.to] = true;
                dis[st][e.to] = p.dis + 1;
                q.push({e.to, p.dis + 1});
            }
        }
    }
}

int main() {
    read(n, m, k);
    for (int i = 0; i < m; i++) {
        int u, v;
        read(u, v);
        G[u].push_back({u, v});
        G[v].push_back({v, u});
    }

    for (int i = 1; i <= n; i++) {
        bfs(i);
    }

    for (int i = 1; i <= n; i++) {
        bfs(i);
    }
}
