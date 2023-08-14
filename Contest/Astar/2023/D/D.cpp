// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>

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

#define int __int128

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int exgcd(int a, int b, int &x, int &y) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= x * (a / b);
    return d;
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int p, q, n1, n2, n3, g;
    read(p, q, n1, n2, n3);
    int a = n2 - n1, b = n3 - n1, c = q - p * n1;

    if (a == 0) {
        while (true);
        int n0 = n1 + n2;
        if (n0 > n3) std::swap(n0, n3);
        int r = q - n0 * p;
        if (n0 == n3) {
            if (q % n0 != 0) {
                puts("-1");
            } else {
                writeln(0, q / n0);
            }
        } else {
            if (r % (n3 - n0) != 0) {
                puts("-1");
            } else {
                writeln(r / (n3 - n0), r / (n3 - n0));
            }
        }
        return 0;
    }

    int x0, y0;
    int gcd = exgcd(a, b, x0, y0);
    if (c % gcd != 0) {
        writeln(-1);
        return 0;
    }
    int x1 = c * x0 / gcd, y1 = c * y0 / gcd;
    // writeln(x1, y1);
    // if (x1 + y1 > p) {
    //     writeln(-1);
    //     return 0;
    // }
    int g1 = b / gcd, g2 = a / gcd;
    int kl = ceil((double) (-x1) / g1), kr = floor((double) (y1) / g2);
    if (kl > kr) {
        puts("-1");
        return 0;
    } else {
        if (x1 + y1 > p) {
            kr -= (x1 + y1 - p) / (g1 - g2);
        }
        if (y1 - g2 * kr > y1 - g2 * kl) writeln(-1);
        else writeln(y1 - g2 * kr, y1 - g2 * kl);
    }
    return 0; 
}
