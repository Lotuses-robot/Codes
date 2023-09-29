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

const int maxn = 1e5 + 10;
int fac[maxn];

int pow(int x, int y, int p) {
    int z = 1;
    do {
        if (y & 1) z *= x, z %= p;
        x *= x; x %= p;
    } while (y >>= 1);
    return z;
}

int Cm(int n, int m, int p) {
    if (m > n) return 0;
    return fac[n] * pow(fac[m], p - 2, p) % p * pow(fac[n - m], p - 2, p) % p;
}

int lucas(int n, int m, int p) {
    if (!m) return 1;
    return Cm(n % p, m % p, p) * lucas(n / p, m / p, p) % p;
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    fac[0] = 1;
    int T;
    read(T);
    while (T--) {
        int n, m, p;
        read(n, m, p);
        for (int i = 1; i <= p; i++) fac[i] = fac[i - 1] * i % p;
        writeln(lucas(n + m, n, p));
    }
    return 0;
}
