// Copyright 2023 Lotuses
#define tsz signed
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

const int maxn = 1e6 + 10;
std::vector<int> G[maxn];

int siz[maxn], n;
void dfs1(int u, int fa) {
    siz[u] = 1;
    for (int v : G[u]) {
        if (v != fa) {
            dfs1(v, u);
            siz[u] += siz[v];
        }
    }
}

int dfs2(int u, int fa) {
    int ans = 0;
    for (int v : G[u]) {
        if (v != fa) {
            ans += siz[v] * (n - siz[v]);
            ans += dfs2(v, u);
        }
    }
    return ans;
}

tsz main() {
    freopen("orient.in", "r", stdin);
    freopen("orient.out", "w", stdout);
    
    int x, y;
    read(n);
    // if (n == 2) {
    //     writeln(4);
    //     return 0;
    // }
    for (int i = 1; i < n; i++) {
        read(x, y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs1(1, 1);
    int ans = n * n * n - 2 * dfs2(1, 1) + n * (n - 1);
    writeln(ans);

    return 0;
}