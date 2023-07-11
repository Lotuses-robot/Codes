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

int n, m;
const int maxn = 400005;
struct Edge {
    int u, v, w;
}; std::vector<Edge> G[maxn];
int in[maxn], out[maxn];
int L[maxn], cnt = 0;
std::vector<Edge> P[maxn];
double p[maxn], f[maxn];

void topo() {
    std::queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (!in[i]) q.push(i);
    }
    while (!q.empty()) {
        int ft = q.front(); q.pop();
        L[++cnt] = ft;
        for (auto e : G[ft]) {
            if (--in[e.v] == 0) {
                q.push(e.v);
            }
        }
    }
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, m);
    for (int i = 1; i <= m; i++) {
        static int u, v, w;
        read(u, v, w);
        G[u].push_back({u, v, w});
        P[v].push_back({v, u, w});
        in[v]++;
        out[u]++;
    }
    topo();

    p[1] = 1;
    for (int i = 2; i <= cnt; i++) {
        for (auto e : P[L[i]]) {
            p[e.u] += 1.0 / out[e.v] * p[e.v];
            f[e.u] += 1.0 / out[e.v] * p[e.v] * e.w;
        }
        // printf("%d %.2lf %.2lf\n", L[i], p[L[i]], f[L[i]]);
    }
    double ans = 0;
    for (int i = 1; i <= n; i++) ans += f[i];
    printf("%.2lf\n", ans);
    return 0;
}
