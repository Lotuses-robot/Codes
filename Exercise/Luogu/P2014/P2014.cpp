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

const int maxn = 105;
struct Edge {
    int u, v, w;
};
std::vector<Edge> G[maxn];

void insert(int u, int v, int w) {
    G[u].push_back({u, v, w});
    G[v].push_back({v, u, w});
}

int f[maxn][maxn];
int fas[maxn];

int dfs(int cur, int q, int fa) {
    fas[cur] = fa;
    if (f[cur][q]) return f[cur][q];
    if (G[cur].size() == 1) {
        if (q >= 1) return -998244353;
        else return 0;
    }
    int ans = -998244353;
    int ss[2], ww[2], cnt = 0;
    for (auto e : G[cur]) {
        if (e.v != fa) {
            ss[cnt] = e.v;
            ww[cnt] = e.w;
            cnt++;
        }
    }
    ans = std::max(dfs(ss[0], q - 1, cur) + ww[0], dfs(ss[1], q - 1, cur) + ww[1]);
    for (int j = 0; q - j - 2 >= 0; j++) {
        ans = std::max(ans, dfs(ss[0], j, cur) + dfs(ss[1], q - j - 2, cur) + ww[0] + ww[1]);
    }
    return f[cur][q] = ans;
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, q;
    read(n, q);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        read(u, v, w);
        insert(u, v, w);
    }

    fas[1] = -1;
    int ans = dfs(1, q, fas[1]);
    writeln(ans);
    return 0;
}
