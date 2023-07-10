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

const int maxn = 305;
struct Edge {
    int u, v;
};
std::vector<Edge> G[maxn];
int w[maxn];
int f[maxn][maxn];
int n, m;

void insert(int u, int v) {
    G[u].push_back({u, v});
    G[v].push_back({v, u});
}

void dfs(int u, int fa) {
    f[u][1] = w[u];
    for (auto e : G[u]) {
        if (e.v != fa) {
            dfs(e.v, u);
            for (int k = m; k >= 1; k--) {
                for (int j = 0; j < k; j++) {
                    f[u][k] = std::max(f[u][k], f[u][k - j] + f[e.v][j]);
                }
            }
        }
    }
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    read(n, m); m++;
    
    for (int i = 1; i <= n; i++) {
        static int x;
        read(x, w[i]);
        insert(i, x);
    }
    
    dfs(0, -1);
    writeln(f[0][m]);
    return 0;
}
