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

const int maxn = 20;
int k, n;
int p[maxn], st[maxn];
double f[102][1 << 17];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int x, y;
    read(k, n);
    for (int i = 1; i <= n; i++) {
        y = 0;
        read(p[i], x);
        while (x) {
            y |= (1 << x);
            read(x);
        }
        st[i] = y;
    }

    for (int i = k; i >= 1; i--) {
        for (int s = 0; s <= (1 << 16) - 1; s++) {
            for (int q = 1; q <= n; q++) {
                if ((s & st[q]) == st[q]) {
                    f[i][s] += std::max(f[i + 1][s], f[i + 1][s | (1 << q)] + p[q]);
                } else {
                    f[i][s] += f[i + 1][s];
                }
            }
            f[i][s] /= n;
        }
    }
    printf("%.6lf", f[1][0]);
    return 0;
}
