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

const int maxn = 50;

int c, n, m, p, t;
int px, py;

#define abs(a) ((a) >= 0 ? (a) : -(a))
#define dis(x, y) (abs((x) - px) + abs((y) - py))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

struct Item {
    int x, y, g, w;
} it[maxn * maxn];

int cnt[maxn * maxn];

int dfs(int day) {
    if (day > t) return 0;
    int ans = 0;
    for (int i = 1; i <= c; i++) {
        if (cnt[i] < 2) {
            cnt[i]++;
            int visc = max(0, min(m, min(it[i].g, (p - (1ll << dis(it[i].x, it[i].y))) / it[i].w)));
            it[i].g -= visc;
            ans = max(ans, dfs(day + 1) + visc);
            it[i].g += visc;
            cnt[i]--;
        }
    }
    return ans;
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(c, n, m, p, t);
    for (int i = 1; i <= c; i++) {
        read(it[i].x, it[i].y, it[i].g, it[i].w);
    }

    int ans = 0;
    for (px = 1; px <= n; px++) {
        for (py = 1; py <= n; py++) {
            ans = max(ans, dfs(1));
        }
    }
    writeln(ans);
    return 0;
}
