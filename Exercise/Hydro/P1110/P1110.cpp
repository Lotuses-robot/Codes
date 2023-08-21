// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
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

#define int long long

const int maxn = 1003;
int f[maxn][maxn];
int g[maxn][maxn];
int v[maxn][maxn];
int n, m;

const int mod = 998244353;

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    read(n, m);
    for (int i = 1; i <= m; i++) {
        for (int j = i + 1; j <= m; j++) {
            if (std::__gcd(i, j) == 1) {
                v[i][++v[i][0]] = j;
                v[j][++v[j][0]] = i;
            }
        }
    }
    v[1][++v[1][0]] = 1;
    for (int j = 1; j <= m; j++) f[1][j] = g[1][j] = 1;
    int ans = 0;
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = 1; k <= v[j][0]; k++) {
                f[i][j] = f[i][j] + f[i - 1][v[j][k]];
                g[i][j] += g[i - 1][v[j][k]];
                if (g[i][j] >= 100000000) {
                    g[i][j] = 1;
                    f[i][j] %= mod;
                }
                // if (f[i][j] >= base) f[i][j] %= mod;
            }
        }
    }
    for (int i = 1; i <= m; i++) {
        ans += f[n][i];
        // ans %= mod;
    }
    writeln(ans);
    return 0;
}