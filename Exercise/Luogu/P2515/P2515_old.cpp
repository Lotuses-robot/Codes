// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
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

const int maxn = 1005;
int n, m;
int w[maxn], v[maxn], d[maxn];
int f[maxn][maxn];
struct Edge {
    int u, v;
}; std::vector<Edge> G[maxn];

void insert(int u, int v) {
    G[u].push_back({u, v});
    G[v].push_back({v, u});
}

void dfs(int u, int fa) {
    f[u][0] = std::max(f[u][0], 0);
    for (auto e : G[u]) {
        if (e.v != fa) {
            dfs(e.v, u);
            for (int j = m; j >= 0; j--) {
                for (int k = 0; k <= j; k++) {
                    f[u][j] = std::max(f[u][j], f[u][j - k] + f[e.v][k]);
                }
            }
        }
    }
    for (int j = m; j >= v[u]; j--) {
        f[u][j] = f[u][j - v[u]] + w[u];
    }
    f[u][v[u]] = std::max(f[u][v[u]], w[u]);
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, m);
    for (int i = 1; i <= n; i++) read(v[i]);
    for (int i = 1; i <= n; i++) read(w[i]);
    for (int i = 1; i <= n; i++) {
        read(d[i]);
        insert(i, d[i]);
    }

    memset(f, -63, sizeof(f));
    dfs(0, -1);
    int ans = 0;
    for (int i = v[0]; i <= m; i++) {
        ans = std::max(ans, f[0][i]);
    }
    writeln(ans);
    return 0;
}
