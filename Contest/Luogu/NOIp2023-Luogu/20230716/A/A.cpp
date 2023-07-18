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

const int maxn = 601005;
struct Edge {
    int u, v, w;
}; std::vector<Edge> G[maxn];

bool vis[maxn];
std::vector<int> Top;

void dfs(int u) {
    vis[u] = true;
    for (Edge e : G[u]) {
        if (!vis[e.v]) dfs(e.v);
    }
}

int val[maxn]; bool fail;
void dfs2(int u) {
    vis[u] = true;
    for (Edge e : G[u]) {
        if (!vis[e.v]) {
            val[e.v] = val[u] ^ e.w;
            dfs2(e.v);
            if (fail) return;
        } else {
            // writeln(val[e.v], val[u], e.w, val[u] ^ e.w);
            if (val[e.v] != (val[u] ^ e.w)) {
                fail = true;
                return;
            }
        }
    }
}

int n, m, k;
void init() {
    memset(vis, 0, sizeof(bool) * (n + 10));
    Top.clear();
    for (int i = 1; i <= n + 10; i++) {
        G[i].clear();
    }
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        nxt: init();
        read(n, m, k);
        for (int i = 1; i <= m; i++) {
            static int u, v, w;
            read(u, v, w);
            G[u].push_back({u, v, w});
            G[v].push_back({v, u, w});
        }
        fail = false;
        for (int i = 1; i <= n; i++) {
            if (!vis[i]) {
                Top.push_back(i);
                dfs(i);
            }
        }
        for (int e : Top) {
            val[e] = 0;
        } 
        val[*Top.rbegin()] = k - 1;
        memset(vis, 0, sizeof(bool) * (n + 10));
        for (int e : Top) {
            dfs2(e);
            if (fail) {
                puts("-1");
                break;
            }
        }
        if (fail) continue;
        for (int i = 1; i <= n; i++) {
            write(val[i]), putchar(' ');
        }
        puts("");
    }
    return 0;
}
