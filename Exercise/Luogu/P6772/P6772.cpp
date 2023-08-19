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

int n, m, T, k;
const int maxn = 50 * 6;
struct Mat {
    int a[maxn + 10][maxn + 10];
    
    Mat operator * (Mat b) const {
        Mat c;
        memset(c.a, -63, sizeof(c.a));
        for (int i = 1; i <= maxn; i++) {
            for (int j = 1; j <= maxn; j++) {
                for (int k = 1; k <= maxn; k++) {
                    c.a[i][j] = std::max(c.a[i][j], a[i][k] + b.a[k][j]);
                }
            }
        }
        return c;
    }

    void print() const {
        for (int i = 1; i <= 18; i++) {
            for (int j = 1; j <= 18; j++) {
                if (a[i][j] < -104426655) {
                    printf("%3d", -1);
                } else {
                    printf("%3d", a[i][j]);
                }
            }
            puts("");
        }
        puts("");
    }
} mt[64];

int a[maxn + 10], b[maxn + 10];
void cal(int kk) {
    memset(b, -63, sizeof(b));
    for (int j = 1; j <= maxn; j++) {
        for (int k = 1; k <= maxn; k++) {
            b[j] = std::max(b[j], a[k] + mt[kk].a[k][j]);
        }
    }
    for (int i = 1; i <= maxn; i++) a[i] = b[i];
}

int c[maxn];
struct de {
    int t, x, y;
    bool operator < (de b) const {
        return t < b.t;
    }
} d[maxn];

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, m, T, k);
    for (int i = 1; i <= n; i++) read(c[i]);
    memset(mt[0].a, -63, sizeof(mt[0].a));
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        read(u, v, w);
        mt[0].a[n * (w - 1) + u][v] = c[v];
    }
    for (int i = n + 1; i <= n * 6; i++) {
        mt[0].a[i - n][i] = 0;
    }
    // mt[0].print();
    for (int i = 1; i <= std::__lg(T) + 1; i++) {
        mt[i] = mt[i - 1] * mt[i - 1];
        // mt[i].print();
    }
    for (int i = 1; i <= k; i++) {
        read(d[i].t, d[i].x, d[i].y);
    }
    std::sort(d + 1, d + k + 1);

    memset(a, -63, sizeof(a));
    a[1] = 0;
    int prev = 0;
    for (int i = 1; i <= k; i++) {
        int dt = d[i].t - prev; int ct = 0;
        do {
            if (dt & 1) cal(ct);
            ct++;
        } while (dt >>= 1);
        a[d[i].x] += d[i].y;
        prev = d[i].t;
    }

    if (prev != T) {
        int dt = T - prev; int ct = 0;
        do {
            if (dt & 1) {
                cal(ct);
                // write(1 << ct), putchar(' ');
                // for (int i = 1; i <= n * 6; i++) {
                //     if (a[i] < -104426655) {
                //         printf("%3d", -1);
                //     } else {
                //         printf("%3d", a[i]);
                //     }
                // }
                // puts("");
            }
            ct++;
        } while (dt >>= 1);
    }

    int ans = a[1] + c[1];
    if (ans < 0) puts("-1");
    else writeln(a[1] + c[1]);
    // mt[0].print();
    return 0;
}
