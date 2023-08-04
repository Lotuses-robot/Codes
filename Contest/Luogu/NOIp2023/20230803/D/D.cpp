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

struct Edge {
    int from, to, cap;
};
struct Node {
    int dis, u;
    bool operator<(Node b) const { return dis > b.dis; }
};
std::vector<Edge> e[200005];
std::priority_queue<Node> q;
int dis[200005];
bool vis[200005];

void ins(int from, int to, int cap) { e[from].push_back({from, to, cap}); e[to].push_back({to, from, cap}); }

void dijkstra(int s) {
    memset(dis, 63, sizeof(dis));
    dis[s] = 0;
    q.push({0, s});
    while (!q.empty()) {
        auto p = q.top();
        q.pop();
        if (vis[p.u])
            continue;
        vis[p.u] = true;
        for (auto ed : e[p.u]) {
            if (dis[ed.to] > dis[ed.from] + ed.cap) {
                dis[ed.to] = dis[ed.from] + ed.cap;
                q.push({dis[ed.to], ed.to});
            }
        }
    }
}

int ee, c;

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, m, q, x, s = 1;
    read(n, m, q, x);

    for (int i = 1; i <= n; i++) read(ee, c);

    for (int i = 1; i <= m; i++) {
        int f, t, c;
        read(f, t, c);
        ins(f, t, c);
    }
    dijkstra(s);
    write(0); putchar(' ');
    for (int i = 2; i <= n; i++)
        write(dis[i] + x), putchar(' ');
    return 0;
}