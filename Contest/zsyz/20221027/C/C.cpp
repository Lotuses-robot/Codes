// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

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

#define maxn 5003
struct Edge {
    int from, to, w;
};
std::vector<Edge> G[maxn];
int dis[maxn], cnt[maxn], vis[maxn];
std::queue<int> q;

bool spfa(int s, int n) {
    memset(dis, 63, sizeof(dis));
    memset(cnt, 0, sizeof(cnt));
    memset(vis, 0, sizeof(vis));
    q.push(s); dis[s] = 0; vis[s] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        vis[u] = 0;
        for (auto e : G[u]) {
            int v = e.to, w = e.w;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= n) return false;
                if (!vis[v]) q.push(v), vis[v] = 1;
            }
        }
    }
    return true;
}

int main() {
    int n, m;
    read(n, m);

    for (int i = 1; i <= n; i++) {
        G[0].push_back({0, i, 0});
    }

    for (int i = 0; i < m; i++) {
        static int c1, c2, y;
        read(c1, c2, y);
        G[c2].push_back({c2, c1, y});
    }

    bool result = spfa(0, n + 1);
    if (!result) {
        puts("NO");
    } else {
        for (int i = 1; i <= n; i++) {
            printf("%d ", dis[i]);
        }
    }
    return 0;
}
