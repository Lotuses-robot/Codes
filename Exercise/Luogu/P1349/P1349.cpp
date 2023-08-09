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

int p, q, a1, a2, n, mod;

const int maxn = 2;
struct Matrix {
    int a[maxn][maxn];
    Matrix operator * (Matrix b) const {
        Matrix c;
        for (int i = 0; i < maxn; i++) {
            for (int j = 0; j < maxn; j++) {
                c.a[i][j] = 0;
                for (int k = 0; k < maxn; k++) {
                    (c.a[i][j] += a[i][k] * b.a[k][j] % mod) %= mod;
                }
            }
        }
        return c;
    }
};

Matrix a, base;

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(p, q, a1, a2, n, mod);
    if (n == 1) {
        writeln(a1);
        return 0;
    } if (n == 2) {
        writeln(a2);
        return 0;
    }
    a.a[0][0] = a2, a.a[0][1] = a1;
    base.a[0][0] = p;
    base.a[0][1] = 1;
    base.a[1][0] = q;
    n -= 2;
    do {
        if (n & 1) a = a * base;
        base = base * base;
    } while (n >>= 1);
    writeln(a.a[0][0]);
    return 0;
}
