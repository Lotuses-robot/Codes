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

const int maxn = 13;
int dis[1 << maxn][1 << maxn];
long long f[maxn][1 << maxn];
int d[maxn][maxn];
int inf;

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    memset(d, 63, sizeof(d));
    // memset(d, 63, sizeof(d));
    inf = d[0][0];

    int n, m;
    read(n, m);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        read(u, v, w);
        d[u][v] = std::min(d[u][v], w);
        d[v][u] = std::min(d[v][u], w);
    }
    for (int i = 0; i < (1 << n); i++) {
        for (int j = i; j; j = (j - 1) & i) {
            int k = i ^ j; long long ans = 0;
            for (int a = 0; a < n; a++) {
                if (k & (1 << a)) {
                    int minn = d[0][0];
                    for (int b = 0; b < n; b++) {
                        if (j & (1 << b)) {
                            minn = std::min(minn, d[b + 1][a + 1]);
                        }
                    }
                    ans += minn;
                }
            }
            dis[i][j] = ans > inf ? inf : ans;
        }
    }

    memset(f, 63, sizeof(f));
    for (int j = 0; j < n; j++) {
        f[1][1 << j] = 0;
    }
    long long ans = f[1][(1 << n) - 1];
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j < (1 << n); j++) {
            for (int k = j; k; k = (k - 1) & j) {
                if (dis[j][j] < inf)
                f[i][j] = std::min(1ll * f[i][j], f[i - 1][k] + 1ll * dis[j][k] * (i - 1));
            }
        }
        ans = std::min(ans, f[i][(1 << n) - 1]);
    }
    writeln(ans);
    return 0;
}
