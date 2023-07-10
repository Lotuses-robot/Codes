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

const int maxn = 20005;
int c[maxn];

struct Edge {
    int u, v;
};
std::vector<Edge> G[maxn];
void insert(int u, int v) {
    G[u].push_back({u, v});
    G[v].push_back({v, u});
}

int ans = -998244353;
int dfs(int cur, int fa = -1) {
    int cans = c[cur];
    for (Edge e : G[cur]) {
        if (e.v != fa) {
            int q = dfs(e.v, cur);
            if (q > 0) cans += q;
        }
    }
    ans = std::max(ans, cans);
    return cans;
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(c[i]);
    }
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        read(u, v);
        insert(u, v);
    }

    dfs(1);
    writeln(ans);
    return 0;
}
