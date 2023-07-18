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

const int maxn = 205;
int s, n, m;
int a[maxn][maxn];
int f[maxn][40015];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(s, n, m);
    for (int i = 1; i <= s; i++) {
        for (int j = 1; j <= n; j++) {
            read(a[j][i]);
        }
    }

    for (int i = 1; i <= n; i++) {
        std::sort(a[i] + 1, a[i] + s + 1);
    }

    memset(f, -63, sizeof(f));
    f[0][0] = 0;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        f[i][0] = std::max(f[i][0], f[i - 1][0]);
        for (int j = 1; j <= m; j++) {
            f[i][j] = std::max(f[i - 1][j], f[i][j]);
            for (int k = 1; k <= s && j - a[i][k] * 2 - 1 >= 0; k++) {
                f[i][j] = std::max(f[i][j], f[i - 1][j - a[i][k] * 2 - 1] + i * k);
                // ans = std::max(ans, f[i][j]);
            }
        }
    }
    for (int j = 0; j <= m; j++) {
        ans = std::max(ans, f[n][j]);
    }
    writeln(ans);
    return 0;
}
