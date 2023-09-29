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
#define debug(arg, args...) { printf("d <%d> ", __LINE__); writeln(arg, ##args); }
#else
#define debug(arg, args...) {}
#endif

#define int long long

const int maxn = 3e6 + 10;
int n, mod;
int fac[maxn];

int pow(int x, int y) {
    int t = 1;
    do {
        if (y & 1) t *= x, t %= mod;
        x *= x; x %= mod;
    } while (y >>= 1);
    return t;
}

int Cm(int n, int m) {
    if (n < m) return 0;
    return fac[n] * pow(fac[m], mod - 2) % mod * pow(fac[n - m], mod - 2) % mod;
}

int Lucas(int n, int m) {
    if (!m) return 1;
    return Cm(n % mod, m % mod) * Lucas(n / mod, m / mod) % mod;
}

int w[maxn];
int dfs(int x) {
    if (x > n) return 1;
    int ans = dfs(x << 1) * dfs((x << 1) | 1) % mod;
    w[x] = w[x << 1] + w[(x << 1) | 1] + 1;
    ans *= Lucas(w[x] - 1, w[x << 1]);
    return ans % mod;
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, mod);
    fac[0] = 1; for (int i = 1; i <= 1000000; i++) fac[i] = fac[i - 1] * i % mod;
    writeln(dfs(1));
    return 0;
}
