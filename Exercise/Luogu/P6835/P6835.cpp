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

const int mod = 998244353;
const int maxn = 1e6 + 10;
struct Edge {
    int u, v;
}; std::vector<Edge> G[maxn];
int f[maxn], sum[maxn];

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    int id, n, m;
    read(id, n, m);
    for (int i = 1; i <= m; i++) {
        static int u, v;
        read(u, v);
        G[u].push_back({u, v});
    }

    for (int i = 1; i <= n; i++) {
        f[i] = G[i].size() + 1;
        for (Edge e : G[i]) {
            f[i] += (sum[i - 1] - sum[e.v - 1]) % mod + mod;
            f[i] %= mod;
        }
        sum[i] = sum[i - 1] + f[i];
        sum[i] %= mod;
    }
    writeln(sum[n]);
    return 0;
}
