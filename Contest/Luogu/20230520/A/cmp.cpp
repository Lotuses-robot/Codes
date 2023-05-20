
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

struct frac {
    int x, y;
    int _gcd(int a, int b) const {
        return std::__gcd(a, b);
    }
    int _lcm(int a, int b) const {
        return a * b / _gcd(a, b);
    }

    bool operator < (const frac b) const {
        int m = _lcm(y, b.y);
        int m1 = m / y, m2 = m / b.y;
        int xa = x * m1, xb = b.x * m2;
        return xa < xb;
    }

    bool operator == (const frac b) const {
        return x == b.x && y == b.y;
    }

    frac operator * (const frac b) const {
        int xm = x * b.x, ym = y * b.y;
        int g = _gcd(xm, ym);
        return {xm / g, ym / g};
    }
};

#define maxn 1000006
int a[maxn];

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".ans", "w", stdout);
    #endif
    
    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
        
        frac x = {1, 1}, maxx = {1, 1};
        int cnt = 1, id = 1;
        for (int j = i; j >= 1; j--, cnt++) {
            x = x * (frac){a[j], cnt};
            debug(x.x, x.y);
            if (maxx < x || maxx == x) {
                maxx = x;
                id = cnt;
            }
        }
        write(id); putchar(' ');
    }
    return 0;
}
