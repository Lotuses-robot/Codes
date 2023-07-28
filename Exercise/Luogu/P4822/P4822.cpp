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

#define int long long

const int maxn = 100;
struct Edge {
    int u, v, w;
};
std::vector<Edge> G[maxn * maxn];
int n, m, k;

// A_i (1 - n) / k (0 - K)
// A_i * (K + 1) + k (pt)
int mp(int u, int q) {
    return u * (k + 2) + q;
    // return q * n + u;
}

void ins(int u, int v, int w) {
    G[u].push_back({u, v, w});
}

struct Node {
    int u, dis;
    bool operator < (const Node b) const {
        return dis > b.dis;
    }
};

int dis[maxn * maxn];
bool vis[maxn * maxn];
std::priority_queue<Node> q;
void dij(int s) {
    q.push({s, 0});
    memset(dis, 63, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    dis[s] = 0;
    while (!q.empty()) {
        Node tp = q.top(); q.pop();
        int u = tp.u, d = tp.dis;
        if (vis[u]) continue;
        vis[u] = true;
        for (Edge e : G[u]) {
            if (d + e.w < dis[e.v]) {
                dis[e.v] = d + e.w;
                q.push({e.v, dis[e.v]});
            }
        }
    }
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    read(n, m, k);
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        read(x, y, z);
        for (int q = 0; q <= k; q++) {
            ins(mp(x, q), mp(y, q), z);
            ins(mp(y, q), mp(x, q), z);
            if (q < k) ins(mp(x, q), mp(y, q + 1), z / 2);
            if (q < k) ins(mp(y, q), mp(x, q + 1), z / 2);
        }
    }

    dij(mp(1, 0));
    int ans = 998244353;
    for (int i = 0; i <= k; i++) {
        ans = std::min(ans, dis[mp(n, i)]);
    }
    writeln(ans);
    return 0;
}
