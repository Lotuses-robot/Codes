// Copyright 2023 Lotuses
#include <cmath>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

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

int n;
const int maxn = 5005;
struct Point {
    int x, y;
} p[maxn];
double diss(Point a, Point b) {
    return sqrt(1ll * (a.x - b.x) * (a.x - b.x) + 1ll * (a.y - b.y) * (a.y - b.y));
}

struct Edge {
    int v;
};
std::vector<Edge> G[maxn];

struct Node {
    double dis;
    int u;
    bool operator < (Node b) const {
        return dis > b.dis;
    }
};
std::priority_queue<Node> q;
double dis[maxn]; bool vis[maxn];
double prim() {
    int cnt = 0;
    double ans = 0;
    dis[1] = 0;
    for (int i = 2; i <= n; i++) dis[i] = 1e18;
    q.push({0, 1});
    while (!q.empty()) {
        int u = q.top().u; q.pop();
        if (vis[u]) continue;
        vis[u] = true;
        cnt++;
        ans += dis[u];
        if (n == cnt) break;
        for (auto e : G[u]) {
            if (dis[e.v] > diss(p[u], p[e.v])) {
                dis[e.v] = diss(p[u], p[e.v]);
                q.push({dis[e.v], e.v});
            }
        }
    }
    return ans;
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n);
    for (int i = 1; i <= n; i++) {
        read(p[i].x, p[i].y);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            G[i].push_back({j});
        }
    }
    printf("%.2lf\n", prim());
    return 0;
}
