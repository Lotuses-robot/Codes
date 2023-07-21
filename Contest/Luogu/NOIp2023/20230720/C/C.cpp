// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <functional>

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

const int maxn = 100005;
struct Item {
    int w, s, p;
    bool operator < (const Item b) const {
        if (w != b.w) return w > b.w;
        if (p != b.p) return p > b.p;
        return s < b.s;
    }
} it[maxn];

int f[894 << 2][894 << 2], g[894 << 2][894 << 2];

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, t;
    read(n, t);
    if (2 * t > n) {
        puts("-1");
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        read(it[i].w, it[i].s, it[i].p);
        it[i].p--;
        if (it[i].p == 0) it[i].p = 3;
    }
    std::sort(it + 1, it + n + 1);

    memset(g, 63, sizeof(g));
    memset(f, 63, sizeof(f));
    const int inf = g[0][0];
    g[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= t; j++) {
            for (int k = 0; k <= t; k++) {
                f[j][k] = g[j][k];
                g[j][k] = inf;
            }
        }
        for (int j = 0; j <= t; j++) {
            for (int k = 0; k <= t; k++) {
                if (it[i].p == 3 || it[i].p == 2) {
                    if (k >= 1) g[j][k] = std::min(g[j][k], f[j][k - 1] + it[i].s);
                }
                if (it[i].p == 2 || it[i].p == 1) {
                    if (j >= 1) g[j][k] = std::min(g[j][k], f[j - 1][k + 1] + it[i].s);
                }
                g[j][k] = std::min(g[j][k], f[j][k]);
            }
        }
    }

    int ans = inf;
    for (int k = 0; k <= t; k++) {
        ans = std::min(ans, g[t][k]);
    }
    if (ans != inf) {
        writeln(ans);
    } else {
        puts("-1");
    }
    return 0;
}
