// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
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
    int from, to, id;
};
std::vector<Edge> G[114514];
int dis[5500];
int lst[5500];
bool vis[5500];
std::queue<int> q;
std::vector<int> e1, e2;

#define min(a, b) ((a) < (b) ? (a) : (b))

void bfs(int s) {
    memset(dis, 63, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    dis[s] = 0;
    q.push(s);

    while (!q.empty()) {
        int p = q.front(); q.pop();
        for (Edge e : G[p]) {
            if (!vis[e.to]) {
                lst[e.to] = e.from;
                dis[e.to] = dis[e.from] + 1;
                q.push(e.to), vis[e.to] = true;
            }
        }
    }
}

int siz = 0;

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
        G[u].push_back({u, v, siz});
        G[v].push_back({v, u, siz});
        siz++;
    }

    int s, t, l;
    read(s, t, l);
    bfs(s);
    // printf("%d\n", dis[t]);
    if (dis[t] > l) {
        puts("-1");
        return 0;
    }
    for (int nd = t; nd != s; nd = lst[nd]) {
        int st = lst[nd];
        for (Edge e : G[st]) {
            if (e.to == nd) {
                e1.push_back(e.id);
                break;
            }
        }
    }

    read(s, t, l);
    bfs(s);
    if (dis[t] > l) {
        puts("-1");
        return 0;
    }
    for (int nd = t; nd != s; nd = lst[nd]) {
        int st = lst[nd];
        for (Edge e : G[st]) {
            if (e.to == nd) {
                e2.push_back(e.id);
                break;
            }
        }
    }

    std::sort(e1.begin(), e1.end());
    std::sort(e2.begin(), e2.end());

    int i = 0, j = 0, ans = e1.size() + e2.size();
    while (i < e1.size() && j < e2.size()) {
        if (e1[i] == e2[j]) {
            ans--;
            i++; j++;
        } else if (e1[i] < e2[j]) {
            i++;
        } else {
            j++;
        }
    }
    
    printf("%d\n", m - ans);
    return 0;
}
