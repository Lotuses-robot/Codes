// Copyright 2023 Lotuses
#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

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
#define gc getchar
#define maxn 105

int n, m, f[maxn][maxn];

struct ahaha {
    int w, to, next;
} e[maxn << 1];
int tot, head[maxn];
inline void add(int u, int v, int w) {
    e[tot] = {w, v, head[u]};
    head[u] = tot++;
}

int sz[maxn];
void dfs(int u, int fa) {
    for (int i = head[u]; ~i; i = e[i].next) {
        int v = e[i].to;
        if (v == fa)
            continue;
        dfs(v, u);
        sz[u] += sz[v] + 1;
        for (int j = std::min(sz[u], m); j; --j)
            for (int k = std::min(sz[v], j - 1); k >= 0; --k)
                f[u][j] = std::max(f[u][j], f[u][j - k - 1] + f[v][k] + e[i].w);
    }
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    memset(head, -1, sizeof(head));
    read(n, m);
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        read(u, v, w);
        add(u, v, w);
        add(v, u, w);
    }
    dfs(1, -1);
    writeln(f[1][m]);
    return 0;
}
