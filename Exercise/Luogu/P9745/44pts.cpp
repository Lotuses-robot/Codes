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
const int maxn = 5e5 + 10, mod = 998244353;
int n, a[maxn];
std::vector<int> G[maxn];
int f[maxn][8];

void dfs(int u, int fa) {
    if (G[u].size() <= 1 && u != fa) {
        // writeln(u, a[u], 1);
        f[u][a[u]] = 1;
    } else {
        int g[2][8];
        int i = 0;
        while (i < G[u].size() && G[u][i] == fa) i++;
        dfs(G[u][i], u);
        memset(g, 0, sizeof(g));
        for (int y = 0; y < 8; y++) {
            g[0][a[u]] += y * f[G[u][i]][y] % mod;
            g[0][a[u]] %= mod;
            g[0][y ^ a[u]] += f[G[u][i]][y];
            g[0][y ^ a[u]] %= mod;
        }
        int c = 1;
        for (i = i + 1; i < G[u].size(); i++, c ^= 1) {
            int v = G[u][i];
            if (v == fa) continue;
            dfs(v, u);
            memset(g[c], 0, sizeof(g[c]));
            for (int x = 0; x < 8; x++) {
                for (int y = 0; y < 8; y++) {
                    g[c][x ^ y] += g[c ^ 1][x] * f[v][y] % mod;
                    g[c][x ^ y] %= mod;
                    g[c][x] += g[c ^ 1][x] * y % mod * f[v][y] % mod;
                    g[c][x] %= mod;
                }
            }
        }
        for (int i = 0; i < 8; i++) {
            f[u][i] = g[c ^ 1][i];
            // writeln(u, i, f[u][i]);
        }
    }
}

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n);
    for (int i = 1; i <= n; i++) read(a[i]);
    for (int i = 2; i <= n; i++) {
        int x; read(x);
        G[i].push_back(x);
        G[x].push_back(i);
    }
    dfs(1, 1);
    int ans = 0;
    for (int i = 0; i < 8; i++) {
        ans += f[1][i] * i % mod;
        ans %= mod;
    }
    writeln(ans);
    return 0;
}