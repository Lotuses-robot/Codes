// Copyright 2023 Lotuses
#define tsz signed
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

const int maxn = 1e5 + 10;
int n, p;
int f[maxn], c[maxn], in[maxn];
struct Edge {
    int v, w;
}; std::vector<Edge> G[maxn];
std::queue<int> q;
std::vector<std::pair<int, int> > ans;

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, p);
    for (int i = 1; i <= n; i++) {
        read(f[i], c[i]);
    }
    for (int i = 1; i <= p; i++) {
        int x, y, z;
        read(x, y, z);
        G[x].push_back({y, z});
        in[y]++;
    }
    for (int i = 1; i <= n; i++) {
        if (f[i] > 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (G[u].empty() && f[u] > 0) {
            ans.push_back({u, f[u]});
        }
        for (Edge e : G[u]) {
            if (f[u] > 0) f[e.v] += e.w * f[u];
            in[e.v]--;
            if (!in[e.v]) {
                f[e.v] -= c[e.v];
                q.push(e.v);
            }
        }
    }
    if (ans.empty()) {
        puts("NULL");
    } else {
        for (auto p : ans) {
            writeln(p.first, p.second);
        }
    }
    return 0;
}