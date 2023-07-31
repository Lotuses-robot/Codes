// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>

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

const int maxn = 500005;
struct Edge {
    int u, v;
};
std::vector<Edge> G[maxn];

int cnt[maxn];

std::vector<int> vis;

void dfs(int u, int fa) {
    vis.push_back({u});
    for (Edge e : G[u]) {
        if (e.v != fa) {
            dfs(e.v, u);
        }
    }
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n;
    read(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        read(u, v);
        G[u].push_back({u, v});
        G[v].push_back({v, u});
        cnt[u]++; cnt[v]++;
    }

    bool flag = false;
    for (int i = 1; i <= n; i++) {
        if (cnt[i] == n - 1) {
            flag = true;
            for (int j = 1; j <= n; j++) {
                if (j != i) printf("%d ", j);
            }
            printf("%d\n", i);
            break;
        }
    }

    if (flag) return 0;

    for (int i = 1; i <= n; i++) {
        if (cnt[i] == 1) {
            dfs(i, -1);
            break;
        }
    }

    for (int i = 0; i < n / 2; i++) {
        writeln(vis[i * 2]);
    }
    if (n & 1) {
        writeln(vis[n - 1]);
    }
    for (int i = n / 2 - 1; i >= 0; i--) {
        writeln(vis[i * 2 + 1]);
    }

    return 0;
}
