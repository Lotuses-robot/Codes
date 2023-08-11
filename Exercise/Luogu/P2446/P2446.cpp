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
    int v, w;
}; std::vector<Edge> G[maxn];
std::vector<int> dag[maxn];
int in[maxn];

struct Node {
    int dis, u;
    bool operator < (Node b) const {
        return dis > b.dis;
    }
};
bool vis[maxn], stage[maxn];
int dis[maxn];
std::priority_queue<Node> q;
int dij() {
    memset(dis, 63, sizeof(dis));
    dis[1] = 0;
    q.push({0, 1});
    while (!q.empty()) {
        int u = q.top().u; q.pop();
        if (vis[u]) continue;
        if (in[u]) {
            stage[u] = true;
            continue;
        }
        vis[u] = true;
        for (Edge e : G[u]) {
            if (dis[e.v] > dis[u] + e.w) {
                dis[e.v] = dis[u] + e.w;
                q.push({dis[e.v], e.v});
            }
        }
        for (int v : dag[u]) {
            in[v]--;
            if (stage[v]) {
                dis[v] = std::max(dis[v], dis[u]);
                if (!in[v]) {
                    q.push({dis[v], v});
                }
            }
        }
    }
    return dis[n];
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int x, y, z;
    read(n, m);
    for (int i = 1; i <= m; i++) {
        read(x, y, z);
        G[x].push_back({y, z});
    }

    for (int i = 1; i <= n; i++) {
        read(x);
        for (int j = 1; j <= x; j++) {
            read(y);
            dag[y].push_back(i);
            in[i]++;
        }
    }

    writeln(dij());
    return 0;
}
