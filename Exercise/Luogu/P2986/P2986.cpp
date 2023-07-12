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

#define int long long

const int maxn = 400005;
int c[maxn];

struct Edge {
    int u, v, w;
}; std::vector<Edge> G[maxn];

void insert(int u, int v, int w) {
    G[u].push_back({u, v, w});
    G[v].push_back({v, u, w});
}

int f[maxn];
int sum[maxn];
void dfs1(int u, int fa, int w) {
    sum[u] = c[u];
    f[1] += w * c[u];
    for (auto e : G[u]) {
        if (e.v != fa) {
            dfs1(e.v, u, w + e.w);
            sum[u] += sum[e.v];
        }
    }
}

void dfs2(int u, int fa) {
    for (auto e : G[u]) {
        if (e.v != fa) {
            f[e.v] = f[u] + e.w * (sum[1] - sum[e.v] * 2);
            dfs2(e.v, u);
        }
    }
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(c[i]);
    }
    for (int i = 1; i < n; i++) {
        static int a, b, l;
        read(a, b, l);
        insert(a, b, l);
    }

    dfs1(1, -1, 0);
    dfs2(1, -1);
    int ans = f[1];
    for (int i = 2; i <= n; i++) {
        ans = std::min(ans, f[i]);
    }
    writeln(ans);
    return 0;
}
