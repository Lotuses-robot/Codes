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

const int maxn = 5005, mod = 1e9 + 7;
int t[maxn], c[maxn], p[maxn];
int f[maxn], g[maxn], f0[maxn][maxn], g0[maxn][maxn];
int cnt = 0;
int itv[maxn << 8];

int log(int q) {
    int cnt = 0;
    while (q != 0) {
        cnt++;
        q >>= 1;
    }
    return cnt;
}

int end[maxn];

void insert(int ma, int t, int id) {
    for (int i = 1; i <= ma; i++) {
        itv[++cnt] = i * t;
    }
    end[id] = cnt;
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    int n, tm, k = 0;
    read(n, tm);

    for (int i = 1; i <= n; i++) {
        read(p[i]); p[i] = log(p[i]);
        insert(p[i], 1, i); k += p[i];
    }

    tm = std::min(tm, k);
    f[0] = g[0] = 1; int cntx = 1;
    f0[0][0] = g0[0][0] = 1;
    for (int i = 1; i <= cnt; i++) {
        if (itv[i] == p[cntx]) {
            for (int v = tm; v >= itv[i]; v--) {
                for (int j = itv[i]; j <= k; j++) {
                    f0[v][j] += g0[v - itv[i]][j - itv[i]] %= mod;
                }
            }
            for (int i = 1; i <= tm; i++) {
                for (int j = 0; j <= k; j++) {
                    g0[i][j] += f0[i][j] %= mod;
                    f0[i][j] = 0;
                }
            }
            cntx++;
            for (int i = 1; i <= tm; i++) {
                g[i] += f[i] %= mod;
                // write(g[i]); putchar(' ');
                f[i] = 0;
            }
            // puts("");
        } else {
            for (int v = tm; v >= itv[i]; v--) {
                f[v] += g[v - itv[i]] %= mod;
                for (int j = 0; j <= k; j++) {
                    f0[v][j] += g0[v - itv[i]][j] %= mod;
                }
            }
        }
    }

    int ans = 0;
    for (int j = 1; j <= k; j++) {
        // ans += g0[i];
        for (int i = j; i <= tm; i++) {
            ans += g0[i][j] %= mod;
        }
        // writeln(g[i]);
    }
    writeln((ans + g[tm]) % mod);
    return 0;
}
