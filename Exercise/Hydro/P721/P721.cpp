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
const int maxn = 10, mod = 1e9 + 7;
struct Matrix {
    int a[10][10];
    Matrix operator * (Matrix b)  {
        Matrix c;
        for (int i = 0; i < maxn; i++) {
            for (int j = 0; j < maxn; j++) {
                c.a[i][j] = 0;
                for (int k = 0; k < maxn; k++) {
                    (c.a[i][j] += (a[i][k] * b.a[k][j] % mod)) %= mod;
                }
            }
        }
        return c;
    }
};

Matrix a, base;

void init() {
    memset(a.a, 0, sizeof(a.a));
    base.a[0][0] = 0; base.a[0][1] = 1; base.a[0][2] = 0; base.a[0][3] = 1; base.a[0][4] = 0; base.a[0][5] = 1; base.a[0][6] = 0; base.a[0][7] = 1; base.a[0][8] = 0; base.a[0][9] = 1;
    base.a[1][0] = 1; base.a[1][1] = 0; base.a[1][2] = 1; base.a[1][3] = 0; base.a[1][4] = 0; base.a[1][5] = 0; base.a[1][6] = 1; base.a[1][7] = 0; base.a[1][8] = 1; base.a[1][9] = 0;
    base.a[2][0] = 0; base.a[2][1] = 1; base.a[2][2] = 0; base.a[2][3] = 0; base.a[2][4] = 0; base.a[2][5] = 1; base.a[2][6] = 0; base.a[2][7] = 1; base.a[2][8] = 0; base.a[2][9] = 0;
    base.a[3][0] = 1; base.a[3][1] = 0; base.a[3][2] = 0; base.a[3][3] = 0; base.a[3][4] = 0; base.a[3][5] = 0; base.a[3][6] = 1; base.a[3][7] = 0; base.a[3][8] = 0; base.a[3][9] = 0;
    base.a[4][0] = 0; base.a[4][1] = 0; base.a[4][2] = 0; base.a[4][3] = 0; base.a[4][4] = 0; base.a[4][5] = 1; base.a[4][6] = 0; base.a[4][7] = 0; base.a[4][8] = 0; base.a[4][9] = 0;
    base.a[5][0] = 1; base.a[5][1] = 0; base.a[5][2] = 1; base.a[5][3] = 0; base.a[5][4] = 1; base.a[5][5] = 0; base.a[5][6] = 1; base.a[5][7] = 0; base.a[5][8] = 0; base.a[5][9] = 0;
    base.a[6][0] = 0; base.a[6][1] = 1; base.a[6][2] = 0; base.a[6][3] = 1; base.a[6][4] = 0; base.a[6][5] = 1; base.a[6][6] = 0; base.a[6][7] = 0; base.a[6][8] = 0; base.a[6][9] = 0;
    base.a[7][0] = 1; base.a[7][1] = 0; base.a[7][2] = 1; base.a[7][3] = 0; base.a[7][4] = 0; base.a[7][5] = 0; base.a[7][6] = 0; base.a[7][7] = 0; base.a[7][8] = 0; base.a[7][9] = 0;
    base.a[8][0] = 0; base.a[8][1] = 1; base.a[8][2] = 0; base.a[8][3] = 0; base.a[8][4] = 0; base.a[8][5] = 0; base.a[8][6] = 0; base.a[8][7] = 0; base.a[8][8] = 0; base.a[8][9] = 0;
    base.a[9][0] = 1; base.a[9][1] = 0; base.a[9][2] = 0; base.a[9][3] = 0; base.a[9][4] = 0; base.a[9][5] = 0; base.a[9][6] = 0; base.a[9][7] = 0; base.a[9][8] = 0; base.a[9][9] = 0;
    a.a[0][0] = 1;
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    int T;
    read(T);
    while (T--) {
        init();
        int k;
        read(k);
        k /= 5; k *= 2;
        do {
            if (k & 1) {
                a = a * base;
            }
            base = base * base;
        } while (k >>= 1);
        // for (int i = 1; i <= k; i++) a = a * base;
        writeln(a.a[0][0]);
    }
    return 0;
}
