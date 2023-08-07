// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

template<typename T>
void read(T &r) { r = 0; static char ch, last; ch = getchar(), last = 'z'; while (ch < '0' || ch > '9') last = ch, ch = getchar(); while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = getchar(); r = (last == '-') ? -r : r; }
template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) { read(arg); read(arg_left...); }

template<typename T>
void write(T x) { if (x < 0) putchar('-'), x = -x; int len = 0; static char ch[100]; while (x) ch[++len] = x % 10 + '0', x /= 10; if (!len) ch[++len] = '0'; while (len) putchar(ch[len--]); }
template<typename T, typename...Ts>
void write(T arg, Ts...arg_left) { write(arg); putchar(' '); write(arg_left...); }
template<typename T>
void writeln(T x) { write(x); putchar('\n'); }
template<typename T, typename...Ts>
void writeln(T arg, Ts...arg_left) { write(arg); putchar(' '); write(arg_left...); putchar('\n'); }

// #define __DEBUG
#ifdef __DEBUG
#define debug(arg, args...) { printf("db <%d> ", __LINE__); writeln(arg, ##args); }
#else
#define debug(arg, args...) {}
#endif

const int maxn = 3005;
int n, m;

struct Edge {
    int u, v, w;
}; std::vector<Edge> G[maxn];

struct Node {
    int dis, u;
    bool operator < (Node b) const {
        return dis > b.dis;
    }
};
std::priority_queue<Node> q;
int dis[4][maxn];
bool vis[maxn];

void dij(int u, int id) {
    memset(dis[id], 63, sizeof(dis[id]));
    memset(vis, 0, sizeof(vis));
    q.push({0, u});
    dis[id][u] = 0;
    while (!q.empty()) {
        Node tp = q.top(); q.pop();
        int &u = tp.u;
        if (vis[u]) continue;
        vis[u] = true;
        for (auto e : G[u]) {
            if (dis[id][e.v] > dis[id][u] + e.w) {
                dis[id][e.v] = dis[id][u] + e.w;
                q.push({dis[id][e.v], e.v});
            }
        }
    }
}

int mp[maxn][maxn];

std::vector<Edge> Gn[2][maxn];
int in[2][maxn];
int f[2][maxn];

std::queue<int> qq;
void topo(int id) {
    for (int i = 1; i <= n; i++) {
        if (!in[id][i]) {
            qq.push(i);
        }
    }
    while (!qq.empty()) {
        int u = qq.front(); qq.pop();
        for (Edge e : Gn[id][u]) {
            f[id][e.v] = std::max(f[id][e.v], f[id][e.u] + e.w);
            in[id][e.v]--;
            if (!in[id][e.v]) qq.push(e.v);
        }
    }
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, m);
    int s1, t1, s2, t2;
    read(s1, t1, s2, t2);
    for (int i = 1; i <= m; i++) {
        static int u, v, w;
        read(u, v, w);
        G[u].push_back({u, v, w});
        G[v].push_back({v, u, w});
    }
    dij(s1, 0); dij(t1, 1); int dis1 = dis[0][t1];
    dij(s2, 2); dij(t2, 3); int dis2 = dis[2][t2];

    for (int i = 1; i <= n; i++) {
        for (auto e : G[i]) {
            if (dis[0][e.u] + e.w + dis[1][e.v] == dis1) {
                mp[e.u][e.v] = true;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (auto e : G[i]) {
            if (dis[2][e.u] + e.w + dis[3][e.v] == dis2) {
                if (mp[e.v][e.u]) {
                    Gn[0][e.u].push_back({e.u, e.v, e.w});
                    in[0][e.v]++;
                }
                if (mp[e.u][e.v]) {
                    Gn[1][e.u].push_back({e.u, e.v, e.w});
                    in[1][e.v]++;
                }
            }
        }
    }

    topo(0);
    topo(1);

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = std::max(ans, std::max(f[0][i], f[1][i]));
    }
    writeln(ans);
    return 0;
}
