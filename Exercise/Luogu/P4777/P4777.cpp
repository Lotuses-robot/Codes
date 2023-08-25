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

#define int __int128

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
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
    
    int n, a1, b1, a2, b2;
    read(n, a2, b2);
    for (int i = 2; i <= n; i++) {
        read(a1, b1);
        if (b2 < b1) std::swap(b1, b2), std::swap(a1, a2);
        int g = gcd(a1, a2);
        if ((b2 - b1) % g != 0) {
            puts("-1");
            return 0;
        }
        int x, y;
        exgcd(a1, a2, x, y);
        // writeln(a1, a2, x, y, q);
        x = (x * (b2 - b1) / g % a2 + a2) % a2;
        int X = b1 + a1 * x;
        // writeln(x, X);
        a2 = a1 * a2 / g;
        b2 = (X + a2) % a2;
        // writeln(a2, b2);
    }
    writeln(b2);
    return 0;
}
