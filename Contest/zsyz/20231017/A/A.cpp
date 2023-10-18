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

const int maxn = 1e6 + 10;
int to[maxn], in[maxn];
int f[maxn][2], g[maxn][2], ans;
std::queue<int> q;

int bfs(int u, int col) {
    g[u][col] = f[u][col] + col;
    g[u][col ^ 1] = -1e9;
    int v = u;
    while (to[v] != u) {
        g[to[v]][0] = f[to[v]][0] + std::max(g[v][0], g[v][1]);
        g[to[v]][1] = f[to[v]][1] + g[v][0] + 1;
        v = to[v];
    }
    if (col) return g[v][0];
    else return std::max(g[v][0], g[v][1]);
}

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(to[i]);
        in[to[i]]++;
    }
    for (int i = 1; i <= n; i++) {
        if (!in[i]) {
            q.push(i);
            f[i][0] = f[i][1] = 0;
        }
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        f[u][1]++;

        f[to[u]][0] += std::max(f[u][0], f[u][1]);
        f[to[u]][1] += f[u][0];
        in[to[u]]--;
        if (!in[to[u]]) q.push(to[u]);
    }
    for (int i = 1; i <= n; i++) {
        if (in[i]) {
            ans += std::max(bfs(i, 0), bfs(i, 1));
            int u = i; in[u] = 0; // writeln(u, f[u][0], f[u][1]);
            while (to[u] != i) in[to[u]] = 0, u = to[u]; //, writeln(u, f[u][0], f[u][1]);
        }
    }
    writeln(ans);
    return 0;
}