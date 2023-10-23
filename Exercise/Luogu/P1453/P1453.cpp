// Copyright 2023 Lotuses
#define tsz signed
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
// #include <map>
// #include <set>
#include <queue>
// #include <algorithm>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

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
#define ins(a, b) (G[a].push_back(b))

#define int long long

const int maxn = 1e6 + 10;
int n;
int p[maxn], ct[maxn], f[maxn][2];
int g[maxn][2];
std::vector<int> G[maxn];
std::queue<int> q;

int to(int u, int fa) {
    for (int v : G[u]) {
        if (v != fa && ct[v] > 1) return v;
    }
    return fa;
}

int bfs(int s, int c) {
    // writeln()
    g[s][c] = f[s][c];
    if (c) g[s][c] += p[s];
    g[s][c ^ 1] = -1e18;
    // writeln(s, g[s][0], g[s][1]);
    int u = s, fa = -1, v = to(u, fa);
    while (v != s) {
        g[v][1] = g[u][0] + f[v][1] + p[v];
        g[v][0] = std::max(g[u][0], g[u][1]) + f[v][0];
        // g[v][0] = std::max(g[u][0] + f[v][0], g[u][1] + f[v][1]);
        fa = u; u = v;
        v = to(u, fa);
        // writeln(u, v, g[u][0], g[u][1]);
    }
    if (c) return g[u][0];
    else return std::max(g[u][1], g[u][0]);
}

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        // freopen(".out", "w", stdout);
    #endif
    
    read(n);
    for (int i = 1; i <= n; i++) {
        read(p[i]);
    }
    for (int i = 1; i <= n; i++) {
        int u, v;
        read(u, v); u++; v++;
        ins(u, v); ins(v, u);
        ct[u]++; ct[v]++;
    }
    for (int i = 1; i <= n; i++) {
        if (ct[i] <= 1) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        f[u][1] += p[u];
        for (int v : G[u]) {
            if (ct[v] <= 1) continue;
            f[v][0] += std::max(f[u][0], f[u][1]);
            f[v][1] += f[u][0];
            ct[v]--;
            if (ct[v] <= 1) {
                q.push(v);
            }
        }
    }
    // writeln(f[2][0], f[2][1], f[3][0], f[3][1]);
    double c4; scanf("%lf", &c4);
    for (int i = 1; i <= n; i++) {
        if (ct[i] > 1) {
            // f[i][1] += p[i];
            // writeln(f[i][0], f[i][1]);
            printf("%.1lf\n", c4 * std::max(bfs(i, 0), bfs(i, 1)));
            return 0;
        }
    }
}