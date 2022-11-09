// Copyright 2022 Lotuses
// this version can get 55pts on offical data
// it only count the first biggest answer to add
//
// but if you count the first biggest answer + the second biggest answer
// you can get **100pts** on offical data
// but it's not a true algorithm (Get WA 95pts on unoffical data)
// (f**k ccf's data)
// need count 3 biggest answer
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

#define int long long

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
std::pair<int, int> ans[3001][3];

void bfs1(int st) {
    memset(vis, 0, sizeof(vis));
    memset(dis[st], 63, sizeof(dis[st]));
    q.push({st, 0});
    dis[st][st] = 0;
    while (!q.empty()) {
        Node p = q.front(); q.pop();
        for (Edge e : G[p.pt]) {
            if (!vis[e.to]) {
                vis[e.to] = true;
                dis[st][e.to] = p.dis + 1;
                // printf("%d %d %d\n", st, e.to, dis[st][e.to]);
                q.push({e.to, p.dis + 1});
            }
        }
    }
}

int sc[3030];

void bfs2() {
    for (int i = 2; i <= n; i++) {
        for (int j = 2; j <= n; j++) {
            if (i != j && dis[1][i] <= k && dis[i][j] <= k) {
                // puts("fk");
                // if (ans[j][0].first < sc[i] + sc[j]) {
                //     ans[j][2] = ans[j][1];
                //     ans[j][1] = ans[j][0];
                //     ans[j][0].first = sc[i] + sc[j];
                //     ans[j][0].second = i;
                //     // printf("1 %d %d %d\n", j, sc[i] + sc[j], i);
                // } else if (ans[j][1].first < sc[i] + sc[j]) {
                //     ans[j][2] = ans[j][1];
                //     ans[j][1].first = sc[i] + sc[j];
                //     ans[j][1].second = i;
                //     // printf("2 %d %d %d\n", j, sc[i] + sc[j], i);
                // } else if (ans[j][2].first < sc[i] + sc[j]) {
                    ans[j][2].first = sc[i] + sc[j];
                    ans[j][2].second = i;
                // }
            }
        }
    }
}

signed main() {
    #ifndef ONLINE_JUDGE
        freopen("data/holiday3.in", "r", stdin);
        freopen("holiday.out", "w", stdout);
    #endif
    read(n, m, k); k++;
    for (int i = 2; i <= n; i++) {
        read(sc[i]);
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        read(u, v);
        G[u].push_back({u, v});
        G[v].push_back({v, u});
    }

    std::pair<int, int> init; init.first = init.second = -1;
    for (int i = 1; i <= n; i++) {
        bfs1(i);
        ans[i][0] = ans[i][1] = ans[i][2] = init;
    }
    // printf("%d %d\n", dis[1][2], dis[2][3]);
    bfs2();

    int anss = -1;
    for (int i = 2; i <= n; i++) {
        for (int j = 2; j <= n; j++) {
            if (i != j && dis[i][j] <= k) {
                for (int a = 2; a < 3; a++) {
                    for (int b = 2; b < 3; b++) {
                        if (ans[i][a].first == -1 || ans[j][b].first == -1) {
                            continue;
                        }
                        if (ans[i][a].second == j
                            || ans[i][a].second == ans[j][b].second
                            || ans[j][b].second == i) continue;
                        anss = std::max(anss, ans[i][a].first
                                            + ans[j][b].first);
                        // printf("%d %d %d %d\n", i, j, ans[i][a].first, ans[j][b].first);   
                    }
                }
            }
        }
    }
    printf("%lld\n", anss);
    return 0;    
}
