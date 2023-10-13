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
const int maxn = 550, mod = 1e9 + 7;
int n;
int a[maxn][maxn];
int f[maxn][maxn], gl[maxn][maxn], gr[maxn][maxn];

int F(int l, int r);
int GL(int l, int r);
int GR(int l, int r);

int GL(int l, int r) {
    if (~gl[l][r]) return gl[l][r];
    gl[l][r] = 0;
    if (l == r) {
        gl[l][r] = 1;
    } else if (l < r) {
        for (int k = l + 1; k <= r; k++) {
            gl[l][r] += F(l, k) * GL(k, r) % mod;
            gl[l][r] %= mod;
        }
    }
    return gl[l][r];
}

int GR(int l, int r) {
    if (~gr[l][r]) return gr[l][r];
    gr[l][r] = 0;
    if (l == r) {
        gr[l][r] = 1;
    } else if (l < r) {
        for (int k = l; k <= r - 1; k++) {
            gr[l][r] += GR(l, k) * F(k, r) % mod;
            gr[l][r] %= mod;
        }
    }
    return gr[l][r];
}

int F(int l, int r) {
    if (~f[l][r]) return f[l][r];
    f[l][r] = 0;
    if (!a[l][r]) return f[l][r];
    if (l == r) {
        f[l][r] = 1;
    } else if (l < r) {
        for (int k = l; k < r; k++) {
            f[l][r] += GL(l, k) * GR(k + 1, r) % mod;
            f[l][r] %= mod;
        }
    }
    return f[l][r];
}

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            read(a[i][j]);
        }
        a[i][i] = 1;
    }

    memset(f, -1, sizeof(f));
    memset(gl, -1, sizeof(gl));
    memset(gr, -1, sizeof(gr));
    writeln(GL(1, n));
    return 0;
}
