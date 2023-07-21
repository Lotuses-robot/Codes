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

const int maxn = 5100;
char a[maxn], b[maxn];
int n, m;
const int mod = 100000000;

int f[maxn], g[maxn], fc[maxn], gc[maxn];

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    scanf("%s%s", a + 1, b + 1);
    n = strlen(a + 1) - 1; m = strlen(b + 1) - 1;
    for (int i = 0; i <= m; i++) {
        gc[i] = 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            f[j] = g[j];
            fc[j] = gc[j];
            g[j] = 0; gc[j] = 0;
        }
        gc[0] = 1;
        for (int j = 1; j <= m; j++) {
            if (a[i] == b[j]) {
                g[j] = f[j - 1] + 1;
                gc[j] = fc[j - 1];
            }
            if (f[j] > g[j]) {
                g[j] = f[j];
                gc[j] = fc[j];
            } else if (f[j] == g[j]) {
                gc[j] += fc[j];
                gc[j] %= mod;
            }
            if (g[j - 1] > g[j]) {
                g[j] = g[j - 1];
                gc[j] = gc[j - 1];
            } else if (g[j - 1] == g[j]) {
                gc[j] += gc[j - 1];
                gc[j] %= mod;
            }
            if (g[j] == f[j - 1]) {
                gc[j] -= fc[j - 1] - mod;
                gc[j] %= mod;
            }
            // printf("%d ", gc[j]);
        }
        // puts("");
    }
    writeln(g[m]);
    writeln(gc[m]);
    return 0;
}
