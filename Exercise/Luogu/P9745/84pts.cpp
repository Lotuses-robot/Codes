// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cassert>
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

#define ll long long
const int maxn = 5e5 + 10, mod = 998244353, ymax = 63;
ll n, a[maxn];
std::vector<int> G[maxn];
int f[maxn][ymax][2];
ll pf[maxn], g[2][ymax][2];

#define get(x, i) (((x) >> (i)) & 1)

void dfs(int u, int fa) {
    // writeln(u);
    if (G[u].size() == 1 && u != fa) {
        // f[u][a[u]] = 1;
        for (int i = 0; i < ymax; i++) {
            f[u][i][get(a[u], i)] = 1;
        }
        pf[u] = 0;
        for (int q = 0; q < ymax; q++) {
            (pf[u] += (1ll << q) % mod * f[u][q][1] % mod) %= mod;
        }
    } else {
        for (int v : G[u]) if (v != fa) dfs(v, u);
        int nt = 0, c = 0, v;
        while (nt < G[u].size() && G[u][nt] == fa) nt++;
        memset(g, 0, sizeof(g));
        v = G[u][nt];
        for (int i = 0; i < ymax; i++) {
            // g[0][y ^ a[u]] += f[G[u][i]][y];
            // g[0][y ^ a[u]] %= mod;
            (g[c][i][get(a[u], i) ^ 0] += f[v][i][0]) %= mod;
            (g[c][i][get(a[u], i) ^ 1] += f[v][i][1]) %= mod;
        }
        for (int i = 0; i < ymax; i++) {
            // g[0][a[u]] += y * f[G[u][i]][y] % mod;
            // g[0][a[u]] %= mod;
            // for (int j = 0; j < ymax; j++) {
                // (g[c][i][get(a[u], i)] += (1ll << j) % mod * f[v][j][1] % mod) %= mod;
            // }
            (g[c][i][get(a[u], i)] += pf[v]) %= mod;
        }
        for (nt = nt + 1, c ^= 1; nt < G[u].size(); nt++, c ^= 1) {
            if (G[u][nt] == fa) continue;
            int v = G[u][nt];
            memset(g[c], 0, sizeof(g[c]));
            for (int j = 0; j < ymax; j++) {
                (g[c][j][0] += (1ll * g[c ^ 1][j][0] * f[v][j][0] % mod + 1ll * g[c ^ 1][j][1] * f[v][j][1] % mod) % mod) %= mod;
                (g[c][j][1] += (1ll * g[c ^ 1][j][0] * f[v][j][1] % mod + 1ll * g[c ^ 1][j][1] * f[v][j][0] % mod) % mod) %= mod;
            }
            for (int j = 0; j < ymax; j++) {
                // for (int q = 0; q < ymax; q++) {
                    // (g[c][j][0] += g[c ^ 1][j][0] * ((1ll << q) % mod) % mod * f[v][q][1] % mod) %= mod;
                    // (g[c][j][1] += g[c ^ 1][j][1] * ((1ll << q) % mod) % mod * f[v][q][1] % mod) %= mod;
                // }
                (g[c][j][0] += 1ll * g[c ^ 1][j][0] * pf[v] % mod) %= mod;
                (g[c][j][1] += 1ll * g[c ^ 1][j][1] * pf[v] % mod) %= mod;
            }
        }
        for (int i = 0; i < ymax; i++) {
            // if (g[c ^ 1][i][0] >= mod) assert(-1);
            f[u][i][0] = g[c ^ 1][i][0];
            f[u][i][1] = g[c ^ 1][i][1];
            // writeln(u, i, f[u][i][0], f[u][i][1]);
        }
        pf[u] = 0;
        for (int q = 0; q < ymax; q++) {
            (pf[u] += (1ll << q) % mod * f[u][q][1] % mod) %= mod;
        }
    }
}

tsz main() {
    #ifdef LOCAL
        freopen("data/xor4.in", "r", stdin);
        // freopen(".out", "w", stdout);
    #endif
    
    read(n);
    for (int i = 1; i <= n; i++) read(a[i]);
    for (int i = 2; i <= n; i++) {
        int x; read(x);
        G[i].push_back(x);
        G[x].push_back(i);
    }
    dfs(1, 1);
    ll ans = 0;
    for (int q = 0; q < ymax; q++) {
        ans += (1ll << q) % mod * f[1][q][1] % mod;
        ans %= mod;
    }
    writeln(ans);
    return 0;
}