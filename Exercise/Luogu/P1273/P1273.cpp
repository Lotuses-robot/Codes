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

const int maxn = 3005;
struct Edge {
    int u, v, w;
};
std::vector<Edge> G[maxn];
int f[maxn][maxn];
int n, m, i;

int dfs(int u) {
    f[u][0] = 0;
    if (G[u].size() == 0) {
        return 1;
    }
    int szz = 0;
    for (auto e : G[u]) {
        int sz = dfs(e.v);
        for (int j = sz + szz; j >= 0; j--) {
            for (int k = 0; k <= sz; k++) {
                f[u][j] = std::max(f[u][j], f[e.v][k] + f[u][j - k] - e.w);
            }
        }
        szz += sz;
    }
    return szz;
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, m);
    for (i = 1; i <= n - m; i++) {
        static int k, a, c;
        read(k);
        for (int j = 1; j <= k; j++) {
            read(a, c);
            G[i].push_back({i, a, c});
        }
    }
    memset(f, -63, sizeof(f));
    for (; i <= n; i++) {
        static int c;
        read(c); f[i][1] = c;
    }
    dfs(1);
    for (int i = m; i >= 0; i--) {
        if (f[1][i] >= 0) {
            writeln(i);
            return 0;
        }
    }
    writeln(0);
    return 0;
}
