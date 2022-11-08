#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

struct Edge {
    int from, to;
};
std::vector<Edge> G[300005];

void ins(int from, int to) {
    G[from].push_back({from, to});
    G[to].push_back({to, from});
}

#define mp(a, b) std::make_pair(a, b)
#define pi std::pair<int, int>
std::queue<pi> q;
bool vis[300005];

#define min(a, b) ((a) < (b) ? (a) : (b))

int bfs() {
    int ans = 1145141919;
    memset(vis, 0, sizeof(vis));
    vis[1] = true;
    q.push(mp(1, 0));
    while (!q.empty()) {
        pi p = q.front(); q.pop();
        if (G[p.first].size() == 2 && p.first != 1) { ans = min(p.second + 2, ans); continue; }
        if (G[p.first].size() == 1 && p.first != 1) { ans = min(ans, p.second + 1); continue; }
        if (G[p.first].size() == 1 && p.first == 1) return 2;
        if (G[p.first].size() == 0) return 1;
        for (Edge e : G[p.first]) {
            if (vis[e.to]) continue;
            q.push(mp(e.to, p.second + 2));
            vis[e.to] = true;
        }
    }
    return ans;
}

int main() {
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
    int n, x, y;
    scanf("%d", &n);

    for (int i = 0; i < n - 1; i++) {
        scanf("%d%d", &x, &y);
        ins(x, y);
    }

    printf("%d\n", n - bfs());
    return 0;
}