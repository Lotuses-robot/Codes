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

const int maxn = 2e5 + 5;
int a[maxn];
struct Edge {
    int v, w;
};
std::vector<Edge> G[maxn];
const int maxa = 1e6 + 5;
int last[maxa];

struct Node {
    int dis, u;
    bool operator < (Node b) const {
        return dis > b.dis;
    }
};
std::priority_queue<Node> q;
bool vis[maxn]; int dis[maxn];
void dij(int s) {
    memset(dis, 63, sizeof(dis));
    dis[s] = 0;
    q.push({dis[s], s});
    while (!q.empty()) {
        int u = q.top().u; q.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (auto e : G[u]) {
            if (dis[e.v] > dis[u] + e.w) {
                dis[e.v] = dis[u] + e.w;
                q.push({dis[e.v], e.v});
            }
        }
    }
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
        if (i != 1) G[i].push_back({i - 1, 1});
        if (i != n) G[i].push_back({i + 1, 1});
    }

    memset(last, -1, sizeof(last));
    for (int i = n; i >= 1; i--) {
        if (last[a[i]] != -1) {
            G[i].push_back({last[a[i]], 1});
        }
        last[a[i]] = i;
    }

    dij(1);
    writeln(dis[n]);
    return 0;
}
