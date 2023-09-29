// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
// #include <bits/extc++.h>

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
const int maxn = 1000 + 10, mod = 1e9 + 7;
char ch[maxn];
int n, kk;
int f[maxn][maxn], g[maxn][maxn], h[maxn][maxn];

bool check(int x, char c) {
    if (ch[x] == '?') return true;
    else if (ch[x] == c) return true;
    return false;
}

bool cks[maxn][maxn];

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, kk);
    scanf("%s", ch + 1);

    memset(cks, 1, sizeof(cks));
    for (int i = 1; i <= n; i++) {
        cks[i][i] = check(i, '*');
        for (int j = i + 1; j <= n; j++) {
            cks[i][j] = cks[i][j - 1] && check(j, '*') && (j - i + 1 <= kk);
        }
    }
    for (int len = 2, j; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            j = i + len - 1;
            // writeln(i, j);
            // (S) (A) (SA) (AS)
            if (check(i, '(') && check(j, ')')) {
                // (S)
                f[i][j] = cks[i + 1][j - 1];
                // writeln(f[i][j]);
                // (A)
                f[i][j] += f[i + 1][j - 1];
                f[i][j] %= mod;
                // writeln(f[i][j]);
                // (SA)
                for (int k = i + 1; k < j - 1; k++) {
                    if (!check(k, '*') || k - i > kk) break;
                    f[i][j] += f[k + 1][j - 1];
                    f[i][j] %= mod;
                }
                // (AS)
                for (int k = j - 1; k > i + 1; k--) {
                    if (!check(k, '*') || j - k > kk) break;
                    f[i][j] += f[i + 1][k - 1];
                    f[i][j] %= mod;
                }
            } else {
                f[i][j] = 0;
            }
            h[i][j] = f[i][j];
            // writeln(f[i][j]);
            // AB
            for (int k = i; k < j; k++) {
                f[i][j] += f[i][k] * h[k + 1][j] % mod;
                f[i][j] %= mod;
                // writeln(f[i][k], h[k + 1][j]);
            }
            // writeln(f[i][j]);
            // AS
            for (int k = j; k > i; k--) {
                // writeln(i, j, k);
                if (!check(k, '*') || j - k + 1 > kk) break;
                g[i][j] += f[i][k - 1];
                g[i][j] %= mod;
            }
            // writeln(f[i][j]);
            // AS B
            for (int k = i; k < j; k++) {
                f[i][j] += g[i][k] * h[k + 1][j];
                f[i][j] %= mod;
            }
            // writeln(f[i][j], g[i][j]);
            // puts("------");
        }
    }
    writeln(f[1][n]);
    return 0;
}
