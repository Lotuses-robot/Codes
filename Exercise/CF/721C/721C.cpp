// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <queue>
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

const int maxn = 5010;
struct Edge {
    int v, w;
}; std::vector<Edge> G[maxn];
int in[maxn];

bool vis[maxn];
void dfs(int u) {
    for (auto e : G[u]) {
        in[e.v]++;
        if (!vis[e.v]) {
            vis[e.v] = true;
            dfs(e.v);
        }
    }
}

std::queue<int> q;
int f[maxn][maxn];
int bak[maxn][maxn];

void topo() {
    memset(f, 0x3f, sizeof(f));
    q.push(1);
    f[1][0] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto e : G[u]) {
            for (int i = 1; i <= 5000; i++) {
                if (f[e.v][i] > f[u][i - 1] + e.w) {
                    f[e.v][i] = f[u][i - 1] + e.w;
                    bak[e.v][i] = u;
                }
            }
            in[e.v]--;
            if (!in[e.v]) q.push(e.v);
        }
    }
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, m, T;
    read(n, m, T);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        read(u, v, w);
        G[u].push_back({v, w});
    }

    dfs(1);
    topo();
    int ai = 0;
    for (int i = 0; i <= 5000; i++) {
        if (f[n][i] <= T) {
            ai = i;
        }
    }
    writeln(ai + 1);
    int pt = n;
    std::vector<int> ans;
    ans.push_back(n);
    for (int i = ai; i >= 1; i--) {
        pt = bak[pt][i];
        ans.push_back(pt);
    }
    std::reverse(ans.begin(), ans.end());
    for (int i : ans) {
        write(i); putchar(' ');
    }
    puts("");
    return 0;
}
