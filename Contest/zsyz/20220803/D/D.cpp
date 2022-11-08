#include <cstdio>
#include <vector>

struct Edge {
    int from, to;
};

std::vector<Edge> G[1000006];
int f[1000006][2];

void insert(int from, int to) {
    G[from].push_back({from, to});
    G[to].push_back({to, from});
}

int tot = 0;

void dfs(int p, int fa) {
    for (Edge e : G[p]) {
        if (e.to == fa) continue;
        dfs(e.to, p);
        f[p][1] += f[e.to][0];
        f[p][0] += f[e.to][1];
    }
    f[p][1]++;
}

#define max(x, y) (((x) > (y)) ? (x) : (y))

int main() {
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n - 1; i++) {
        int f, t;
        scanf("%d%d", &f, &t);
        insert(f, t);
    }
    dfs(1, -1);
    printf("%d\n", max(f[1][0], f[1][1]));
    return 0;
}