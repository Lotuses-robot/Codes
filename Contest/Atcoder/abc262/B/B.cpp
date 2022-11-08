#include <cstdio>
#include <vector>

struct Edge {
    int from, to;
};
std::vector<Edge> G[1145];
int ToT[102][102];

void insert(int u, int v) {
    G[u].push_back({u, v});
    G[v].push_back({v, u});
}

int main() {
    int n, m, ans = 0;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        ans += ToT[u][v];
        for (Edge e : G[u]) {
            ToT[v][e.to]++;
            ToT[e.to][v]++;
        }
        for (Edge e : G[v]) {
            ToT[u][e.to]++;
            ToT[e.to][u]++;
        }
        insert(u, v);
    }
    printf("%d\n", ans);
    return 0;
}