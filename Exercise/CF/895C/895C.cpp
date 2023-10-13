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

#define ll long long

const int maxn = (1 << 19), mx = (1e5 + 10), p[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67 }, mod = 1e9 + 7;
ll f[2][maxn], pow2[mx];
int cnt[80];

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, a;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a);
        cnt[a]++;
    }

    pow2[0] = 1;
    for (int i = 1; i <= n; i++) pow2[i] = (pow2[i - 1] << 1) % mod;
    int op = 0;
    f[op][0] = 1;
    for (int i = 1; i <= 70; i++) {
        if (!cnt[i]) continue;
        op ^= 1;
        memset(f[op], 0, sizeof(f[op]));
        for (int j = 0; j < (1 << 19); j++) {
            int nxt = j, y = i;
            for (int k = 0; k < 19 && y >= p[k]; k++) {
                while (y % p[k] == 0) nxt ^= (1 << k), y /= p[k];
            }
            (f[op][nxt] += f[op ^ 1][j] * pow2[cnt[i] - 1] % mod) %= mod;
            (f[op][j] += f[op ^ 1][j] * pow2[cnt[i] - 1] % mod) %= mod;
        }
    }
    writeln((f[op][0] - 1 + mod) % mod);
    return 0;
}