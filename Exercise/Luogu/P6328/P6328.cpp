// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <bitset>
#include <algorithm>

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
std::vector<Edge> G[1005];
std::queue<int> q;
int dis[1005][1005];
bool vis[1005];
int maps[1005][1005];
std::bitset<1005> bs[1005][1005];

void bfs(int s) {
    memset(vis, 0, sizeof(vis));
    memset(dis[s], 63, sizeof(dis[s]));

    dis[s][s] = 0; vis[s] = true; q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (Edge e : G[u]) {
            if (!vis[e.to]) {
                vis[e.to] = true;
                dis[s][e.to] = dis[s][e.from] + 1;
                q.push(e.to);
            }
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
        for (int j = 1; j <= n; j++) {
            if (dis[i][j] <= 2000) bs[i][dis[i][j]].set(j, 1);
        }
        for (int j = 1; j <= n; j++) {
            bs[i][j] |= bs[i][j - 1];
        }
    }

    while (q--) {
        int a; read(a);
        static std::bitset<1005> ans; ans.reset();
        for (int i = 0; i < a; i++) {
            int a, b;
            read(a, b);
            ans |= bs[a][b];
            // for (int i = 1; i <= n; i++) {
            //     printf("%d", ans.test(i));
            // } puts("");
        }
        printf("%d\n", ans.count());
    }
    return 0;
}
