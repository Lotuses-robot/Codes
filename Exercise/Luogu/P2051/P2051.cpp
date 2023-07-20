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
const int mod = 9999973;
const int maxn = 200;
int f[maxn][maxn][maxn];
int C(int c) {
    return c * (c - 1) / 2;
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    int n, m;
    read(n, m);
    f[0][0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int k = 0; k <= m; k++) {
                f[i][j][k] += f[i - 1][j][k]; f[i][j][k] %= mod;
                if (j >= 1) f[i][j][k] += f[i - 1][j - 1][k + 1] * (k + 1) % mod;
                if (k >= 1) f[i][j][k] += f[i - 1][j][k - 1] * (m - j - (k - 1)) % mod;
                if (k >= 2) f[i][j][k] += f[i - 1][j][k - 2] * C(m - j - (k - 2)) % mod;
                if (j >= 1) f[i][j][k] += f[i - 1][j - 1][k] * k * (m - (j - 1) - k) % mod;
                if (j >= 2) f[i][j][k] += f[i - 1][j - 2][k + 2] * C(k + 2) % mod;
                f[i][j][k] %= mod;
            }
        }
    }
    int ans = 0;
    for (int j = 0; j <= m; j++) {
        for (int k = 0; k <= m; k++) {
            ans += f[n][j][k]; ans %= mod;
            // writeln(j, k, f[n][j][k]);
        }
        // puts("");
    }
    writeln(ans);
    return 0;
}
