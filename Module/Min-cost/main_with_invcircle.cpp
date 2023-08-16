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

const int maxn = 3e2 + 10;
struct Edge {
    int v, nxt;
    ll cap, cost;    
} node[30010];
int cnt = 0, head[maxn], n, m, st, ed;
void ins(int u, int v, ll w, ll c) {
    int id = cnt++;
    node[id].nxt = head[u];
    node[id].cap = w;
    node[id].cost = c;
    node[id].v = v;
    head[u] = id;
}
void inse(int u, int v, int w, int c) {
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
            // dis[u] = 0;
            break;
        }
    }
    if (used == 0) dis[u] = 0;
    vis[u] = false;
    return used;
}
void Dinic() {
    while (spfa(s, t)) {
        memcpy(cur, head, (n + 5) * sizeof(int));
        sum += dfs(s, 1e10);
    }
}

ll tot[maxn];
int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        // freopen(".out", "w", stdout);
    #endif
    
    memset(head, -1, sizeof(head));
    read(n, m, st, ed);
    for (int i = 1; i <= m; i++) {
        int x, y, f, v;
        read(x, y, f, v);
        if (v >= 0) inse(x, y, f, v);
        else {
            inse(y, x, f, -v);
            tot[x] -= f; tot[y] += f;
            cost += f * v;
        }
    }
    // writeln(1);
    s = n + 1; t = n + 2;
    for (int i = 1; i <= n; i++) {
        if (tot[i] > 0) inse(s, i, tot[i], 0);
        else inse(i, t, -tot[i], 0);
    }
    Dinic();
    s = st; t = ed; sum = 0; n -= 2;
    Dinic();
    writeln(sum, cost);
    return 0;
}
