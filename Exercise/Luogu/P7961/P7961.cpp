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

const int maxn = 35, maxm = 105, mod = 998244353;
int n, m, ku;
int v[maxm][maxn];
int f[maxm][maxn][maxm][maxn];
int C[maxm][maxm];

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, m, ku);
    for (int i = 0; i <= m; i++) {
        v[i][0] = 1;
        read(v[i][1]);
        for (int j = 2; j <= n; j++) {
            v[i][j] = v[i][j - 1] * v[i][1] % mod;
        }
    }
    for (int i = 0; i <= 100; i++)
        for (int j = 0; j <= i; j++)
            if (!j) C[i][j] = 1;
            else C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
        
    // writeln(C[6][6]);
    f[0][0][0][0] = 1;
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= ku; k++) {
                for (int p = 0; p <= n >> 1; p++) {
                    for (int t = 0; t <= n - j; t++) {
                        f[i + 1][j + t][k + (t + p) % 2][(t + p) / 2] += f[i][j][k][p] * v[i][t] % mod * C[n - j][t] % mod;
                        f[i + 1][j + t][k + (t + p) % 2][(t + p) / 2] %= mod;
                        // if (i + 1 == m + 1 && j + t == n) {
                        //     // writeln(n - j, t);
                        //     // writeln(i, j, k, p, f[i][j][k][p], C[n - j][t], f[i + 1][j + t][k + (t + p) % 2][(t + p) / 2]);
                        // }
                    }
                }
            }
        }
    }

    int ans = 0;
    for (int k = 0; k <= ku; k++)
	    for (int p = 0; p <= n >> 1; p++) {
            // writeln(f[m + 1][n][k][p]);
			if (k + __builtin_popcount(p) <= ku) {
                ans = (ans + f[m + 1][n][k][p]) % mod;
            }
        }

    writeln(ans);
    return 0;
}