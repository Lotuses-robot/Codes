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

const int maxn = 12004;
int r[maxn];

struct Edge {
    int u, v;
};
std::vector<Edge> G[maxn];
int faa[maxn];
int rem[maxn][2];

int dfs(int cur, int t) {
    if (rem[cur][t] != 0) {
        return rem[cur][t];
    }
    if (G[cur].size() == 0) {
        if (t == 0) return 0;
        else return rem[cur][t] = r[cur];
    }
    int ans = 0;
    if (t == 0) {
        for (Edge e : G[cur]) {
            ans += std::max(dfs(e.v, 0), dfs(e.v, 1));
        }
    } else {
        for (Edge e : G[cur]) {
            ans += dfs(e.v, 0);
        }
        ans += r[cur];
    }
    return rem[cur][t] = ans;

}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(r[i]);
    }

    int u, v;
    for (int i = 1; i <= n - 1; i++) {
        read(u, v);
        G[v].push_back({v, u});
        faa[u]++;
    }
    int fa;
    for (int i = 1; i <= n; i++) {
        if (!faa[i]) {
            fa = i;
            break;
        }
    }
    writeln(std::max(dfs(fa, 1), dfs(fa, 0)));
    return 0;
}
