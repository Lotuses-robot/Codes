// Copyright 2023 Lotuses
#include <cmath>
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

int exgcd(int a, int b, int &x, int &y) {
    if (!b) { x = 1, y = 0; return a; }
    int d = exgcd(b, a % b, x, y);
    int t = x;
    x = y;
    y = t - (a / b) * y;
    return d;
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        int a, b, c, x0, y0;
        read(a, b, c);
        int gcd = exgcd(a, b, x0, y0);
        if (c % gcd != 0) {
            writeln(-1);
            continue;
        }
        int x1 = c * x0 / gcd, y1 = c * y0 / gcd;
        int g1 = b / gcd, g2 = a / gcd;
        int kl = ceil((double) (-x1 + 1) / g1), kr = floor((double) (y1 - 1) / g2);
        if (kl > kr) {
            int s1 = ceil((double)(-x1 + 1) / g1), s2 = floor((double)(y1 - 1) / g2);
            writeln(x1 + g1 * s1, y1 - g2 * s2);
        } else {
            writeln(kr - kl + 1, x1 + g1 * kl, y1 - g2 * kr, x1 + g1 * kr, y1 - g2 * kl);
        }
    }
    return 0;
}
