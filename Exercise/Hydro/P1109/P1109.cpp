// Copyright 2023 Lotuses
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

#define ll long long

const int maxn = 1e5 + 10;
struct Edge {
    int v, nxt;
    ll cap, cost;    
} node[maxn];
int idx = 0, head[maxn], n, m;
void ins(int u, int v, ll w, ll c) {
    int id = idx++;
    node[id].nxt = head[u];
    node[id].cap = w;
    node[id].cost = c;
    node[id].v = v;
    head[u] = id;
}
void inse(int u, int v, int w, int c) {
    // writeln(u, v, w);
    ins(u, v, w, c);
    ins(v, u, 0, -c);
}
int s, t, sum = 0, cost = 0;
int dis[maxn]; bool vis[maxn];
int cur[maxn];
std::queue<int> q;
bool spfa(int s, int t) {
    memset(dis, 0x3f, sizeof(dis));
    q.push(s); dis[s] = 0; vis[s] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        // writeln(u, dis[u]);
        vis[u] = false;
        for (int i = head[u]; ~i; i = node[i].nxt) {
            int v = node[i].v;
            if (node[i].cap && dis[v] > dis[u] + node[i].cost) {
                dis[v] = dis[u] + node[i].cost;
                if (!vis[v]) q.push(v), vis[v] = true;
            }
        }
    }
    return dis[t] != 0x3f3f3f3f;
}
ll dfs(int u, ll f) {
    if (u == t || f == 0) return f;
    vis[u] = true;
    ll used = 0, fl = 0;
    for (int i = cur[u]; ~i; i = node[i].nxt) {
        cur[u] = i;
        Edge &e = node[i];
        if (!vis[e.v] && dis[e.v] == dis[u] + e.cost && e.cap) {
            fl = dfs(e.v, std::min(f - used, e.cap));
            if (fl) {
                e.cap -= fl;
                node[i ^ 1].cap += fl;
                used += fl;
                cost += e.cost * fl;
            }
        }
        if (used == f) {
            break;
        }
    }
    if (used == 0) dis[u] = 0;
    vis[u] = false;
    return used;
}
void Dinic() {
    while (spfa(s, t)) {
        // puts("??");
        memcpy(cur, head, sizeof(cur));
        sum += dfs(s, 1e12);
    }
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        // freopen(".out", "w", stdout);
    #endif
    
    memset(head, -1, sizeof(head));

    int sc, tc;
    read(n, m, sc, tc);

    n += 2;
    s = n - 1;
    t = n;

    for (int i = 1; i <= n - 2; i++) {
        int v;
        read(v);
        inse(i, i + n, v, 0);
    }
    for (int i = 1; i <= sc; i++) {
        int v;
        read(v);
        inse(s, v, 0x7f7f7f7f, 0);
    }
    for (int i = 1; i <= tc; i++) {
        int v;
        read(v);
        inse(v + n, t, 0x7f7f7f7f, 0);
    }
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        read(u, v, w);
        inse(u + n, v, 0x7f7f7f7f, w);
        inse(v + n, u, 0x7f7f7f7f, w);
    }
    // n += n - 2;
    Dinic();
    writeln(sum, cost);
    return 0;
}
