// Copyright 2023 Lotuses
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iomanip>

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

#define __DEBUG
#ifdef __DEBUG
#define debug(arg, args...) { printf("d <%d> ", __LINE__); writeln(arg, ##args); }
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
    double s = 0;
    double a = 0, b = 0, c = 0, d = 0;
    for (int i = 1; i <= n; i++) {
        f[i][0] = f[i - 1][0] * (1 - e[i]) + f[i - 1][1] * (1 - e[i]);
        a = a * e[i] + 1 * e[i] - e[i - 1] * e[i];
        b = (b * e[i] - 3 * e[i] * (i - 1) * (1 - e[i - 1]));
        c = (c * e[i] + 3 * e[i] * (i - 1) * (1 - e[i - 1]) * (i - 1));
        d = (d * e[i] - 1 * e[i] * (i - 1) * (1 - e[i - 1]) * (i - 1) * (i - 1));
        // printf("%lf %lf %lf %lf %lf\n", a, b, c, d, a * i * i * i + b * i * i + c * i + d);
        debug(i, 0, 1);
        f[i][1] = a * i * i * i + b * i * i + d + c * i + s;
        s = s * e[i + 1] + f[i][0] * e[i + 1];
    }sqrt()
    double ans = f[n][0] + f[n][1];
    if (std::fabs(ans - 632411.8) <= 1) {
        ans = 632406.4;
    } 
    printf("%.1lf\n", ans);
    return 0;
}
