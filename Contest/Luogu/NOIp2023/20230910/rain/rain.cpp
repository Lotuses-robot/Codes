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

const int maxn = 4010, mod = 1e9 + 7;
int n;
int w[maxn];
int f[2][maxn][3], s1[2][maxn], s2[2][maxn];

int pow(int x, int y) {
    int z = 1;
    for (int i = 1; i <= y; i++) z *= x;
    return z % mod;
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n);
    for (int i = 1; i <= n; i++) {
        read(w[i]);
    }

    for (int j = 1; j <= n; j++) {
        f[1][j][0] = 1 * w[j]; f[1][j][1] = j * w[j] % mod; f[1][j][2] = j * j * w[j] % mod;
    }

    int ans = 0, x, i;
    for (x = 1, i = 1; x <= n - 3; x++, i ^= 1) {
        // init s
        for (int j = 1; j <= n; j++) {
            s1[i][j] = s1[i][j - 1] + f[i][j][0]; s1[i][j] %= mod;
            s2[i][j] = s2[i][j - 1] + f[i][j][0] * (j - 1) * (j - 1) % mod + f[i][j][1] * (j - 1) % mod + f[i][j][2]; s2[i][j] %= mod;
        }

        for (int j = 1; j <= n; j++) {
            for (int k = 0; k <= 2; k++) {
                f[i ^ 1][j][k] = 0;
            }
        }

        for (int j = 1; j <= n; j++) {
            for (int k = 0; k <= 2; k++) {
                if (k > 0) (f[i ^ 1][j][k - 1] += f[i][j][k]) %= mod;
                if (k == 2) {
                    (f[i ^ 1][j][k] += s2[i][j]) %= mod;
                }
                (f[i ^ 1][j][k] += pow(j, k) * (s1[i][n] - s1[i][j]) % mod) %= mod;
            }
            // writeln(i, j, 2, f[i][j][2], w[j]);
        }

        for (int j = 1; j <= n; j++) {
            for (int k = 0; k <= 2; k++) {
                (f[i ^ 1][j][k] *= w[j]) %= mod;
            }
        }
    }
    for (int j = 1; j <= n; j++) {
        ans = (ans + f[i][j][2] + f[i][j][1] * (j - 1) % mod + f[i][j][0] * (j - 1) * (j - 1) % mod) % mod;
    }
    writeln((ans + mod) % mod);
    return 0;
}