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

const int maxn = 3e5 + 5;
int n, m;
struct Edge {
    int v, w;
};
std::vector<Edge> G[maxn];
struct Node {
    int dis, u;
    bool operator < (Node b) const {
        if (dis != b.dis) return dis > b.dis;
        return u < b.u;
    }
};
std::priority_queue<Node> q;
int dis[maxn]; bool vis[maxn];
bool ed[maxn];

int dij() {
    while (!q.empty()) {
        int u = q.top().u; q.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (auto e : G[u]) {
            if (dis[e.v] > dis[u] + e.w) {
                // auto p = q.lower_bound({dis[e.v], e.v});
                // if (p != q.end()) q.erase(p);
                dis[e.v] = dis[u] + e.w;
                q.push({dis[e.v], e.v});
            }
        }
    }
    int min = 1e18;
    for (int i = 1; i <= n; i++) {
        if (ed[i]) min = std::min(min, dis[i]);
    }
    if (min == 1e18) return -1;
    return min;
}

signed main() {
    #ifdef LOCAL
        freopen("data4.in", "r", stdin);
        freopen("data4.out", "w", stdout);
    #endif

    read(n, m);
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        read(x, y, z);
        G[x].push_back({y, z});
    }

    memset(dis, 63, sizeof(dis));

    int a, b;
    read(a, b);
    for (int i = 1; i <= a; i++) {
        int x;
        read(x);
        q.push({0, x});
        dis[x] = 0;
        // writeln(666, i);
    }

    for (int i = 1; i <= b; i++) {
        int x;
        read(x);
        ed[x] = true;
    }

    writeln(dij());
    return 0;
}
