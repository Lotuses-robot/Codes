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

int ps[101], p[101], pre[101];
int f[101][101][2];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    memset(f, 63, sizeof(f));
    int n, c, l, r = -1;
    read(n, c);
    for (int i = 1; i <= n; i++) {
        read(ps[i], p[i]);
        pre[i] = pre[i - 1] + p[i];
    }

    f[c][c][0] = f[c][c][1] = 0;
    
    for (int len = 1; len < n; len++) {
        for (int i = 1; i <= n - len; i++) {
            int j = i + len;
            f[i][j][0] = std::min(f[i + 1][j][0] + (pre[n] - pre[j] + pre[i]) * (ps[i + 1] - ps[i]),
                                  f[i + 1][j][1] + (pre[n] - pre[j] + pre[i]) * (ps[j] - ps[i]));
            f[i][j][1] = std::min(f[i][j - 1][0] + (pre[n] - pre[j - 1] + pre[i - 1]) * (ps[j] - ps[i]),
                                  f[i][j - 1][1] + (pre[n] - pre[j - 1] + pre[i - 1]) * (ps[j] - ps[j - 1]));
            // writeln(i, j, f[i][j][0], f[i][j][1], pre[n] - pre[j - 1] + pre[i - 1]);
        }
    }
    int ans = std::min(f[1][n][0], f[1][n][1]);
    printf("%d\n", ans);
    return 0;
}
