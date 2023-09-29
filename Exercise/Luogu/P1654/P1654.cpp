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

const int maxn = 1e5 + 10;
double e[maxn];
double f[maxn][2];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        scanf("%lf", &e[i]);
    }
    double s = 0, p = 1;
    for (int i = 1; i <= n; i++) {
        f[i][0] = (f[i - 1][0] + f[i - 1][1]) * (1 - e[i]);
        for (int j = 0; j < i; j++) {
            double p = 1;
            for (int k = j + 1; k <= i; k++) {
                p *= e[k];
            }
            f[i][1] += (f[j][0] + (i - j) * (i - j) * (i - j) * (1 - e[j])) * p;
            // printf("dbg %lf %lf\n", f[j][0] * p, (i - j) * (i - j) * (i - j) * (1 - e[j]) * p);
        }
    }
    printf("%.1lf\n", f[n][0] + f[n][1]);
    return 0;
}
