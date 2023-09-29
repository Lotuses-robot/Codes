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
const int maxn = 1e6 + 10, mod = 998244353;
int n;
std::vector<int> G[maxn];

int qpow(int a, int x) {
    int c = 1;
    do {
        if (x & 1) c *= a, c %= mod;
        a *= a; a %= mod;
    } while (x >>= 1);
    return c;
}

int inv(int x) {
    return qpow(x, mod - 2);
}

int f[maxn], g[maxn], h[maxn], siz[maxn], A[maxn], iA[maxn];
void dfs1(int u, int fa) {
    siz[u] = 0; g[u] = h[u] = 1;
    for (int v : G[u]) {
        if (v != fa) {
            dfs1(v, u);
            siz[u] += siz[v];
            g[u] *= f[v]; g[u] %= mod;
            h[u] *= iA[siz[v]]; h[u] %= mod;
        }
    }
    h[u] *= A[siz[u]]; h[u] %= mod;
    siz[u]++;
    f[u] = g[u] * h[u] % mod;
    // writeln(u, g[u], h[u], f[u]);
}

int ans[maxn];
void dfs2(int u, int fa) {
    for (int v : G[u]) {
        if (v != fa) {
            int t = ans[u] * inv(f[v]) % mod * A[siz[v]] % mod * iA[siz[1] - 1] % mod * A[siz[1] - 1 - siz[v]] % mod;
            ans[v] = f[v] * t % mod * iA[siz[v] - 1] % mod * A[siz[1] - 1] % mod * iA[siz[1] - siz[v]] % mod;
            dfs2(v, u);
        }
    }
}

signed main() {
    // #ifdef LOCAL
        // freopen(".in", "r", stdin);
        // freopen(".out", "w", stdout);
    // #endif
    
    read(n);
    A[0] = 1; iA[0] = 1;
    for (int i = 1; i <= n; i++) A[i] = A[i - 1] * i % mod, iA[i] = inv(A[i]);
    for (int i = 1; i < n; i++) {
        int u, v;
        read(u, v);
        G[u].push_back(v);
        G[v].push_back(u);
    }

    dfs1(1, -1);
    ans[1] = f[1];
    // writeln(f[1]);
    dfs2(1, -1);
    int anss = 0;
    for (int i = 1; i <= n; i++) {
        anss += ans[i];
        anss %= mod;
        // writeln(i, ans[i]);
    }
    writeln(anss);
    return 0;
}
