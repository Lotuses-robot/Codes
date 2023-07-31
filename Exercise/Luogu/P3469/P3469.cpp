// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
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

#define int long long

const int maxn = 400004;
int n, m;
struct Edge {
    int u, v;
}; std::vector<Edge> G[maxn];

std::vector<int> Gx[maxn];

std::vector<int> ans;
bool ansb[maxn];
int dfn[maxn], low[maxn], cnt = 0;
int sz[maxn];
void tarjan(int u, int fa) {
    dfn[u] = low[u] = ++cnt; sz[u] = 1;
    int son = 0, sons = 0;
    for (auto e : G[u]) {
        if (!dfn[e.v]) {
            son++;
            tarjan(e.v, u);
            low[u] = std::min(low[u], low[e.v]);
            sz[u] += sz[e.v];
            if (u == fa) {
                Gx[u].push_back(sz[e.v]);
            }
            if (u != fa && low[e.v] >= dfn[u]) {
                sons += sz[e.v];
                Gx[u].push_back(sz[e.v]);
            }
            if (u != fa && (!ansb[u]) && low[e.v] >= dfn[u]) {
                ansb[u] = true;
                ans.push_back(u);
            }
        } else if (e.v != fa) {
            low[u] = std::min(low[u], dfn[e.v]);
        }
    }
    if (u != fa) Gx[u].push_back(n - sons - 1);
    if (u == fa && son >= 2 && (!ansb[u])) {
        ansb[u] = true;
        ans.push_back(u);
    }
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, m);
    for (int i = 1; i <= m; i++) {
        static int a, b;
        read(a, b);
        G[a].push_back({a, b});
        G[b].push_back({b, a});
    }

    tarjan(1, 1);

    for (int i = 1; i <= n; i++) {
        int ans = 2 * (n - 1);
        for (int e : Gx[i]) {
            // writeln(i, e);
            ans += e * (n - e - 1);
        }
        writeln(ans);
    }

    // for (int i = 1; i <= n; i++) {
    //     if (!dfn[i]) tarjan(i, i);
    // }


    // std::sort(ans.begin(), ans.end());
    // writeln(ans.size());
    // for (int e : ans) {
    //     write(e); putchar(' ');
    // }
    // puts("");
    return 0;
}
