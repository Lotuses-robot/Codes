// Copyright 2023 Lotuses
#define tsz signed
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

const int maxn = 1e6 + 10, mod = 1e9 + 7;
int n, m, cnt, p[maxn], s[maxn];
int lc[maxn], rc[maxn];
std::vector<std::vector<int> > f;

void dfs(int u) {
    for (int i = 1; i <= m; i++) f[u][i] = 1;
    if (lc[u]) dfs(lc[u]);
    if (rc[u]) dfs(rc[u]);
    if (lc[u]) for (int i = 1; i <= m; i++) f[u][i] = f[u][i] * f[lc[u]][i - 1] % mod;
    if (rc[u]) for (int i = 1; i <= m; i++) f[u][i] = f[u][i] * f[rc[u]][i] % mod;
    for (int i = 2; i <= m; i++) f[u][i] = (f[u][i] + f[u][i - 1]) % mod;
}

void init() {
    for (int i = 1; i <= cnt; i++) s[i] = 0;
    for (int i = 1; i <= n; i++) lc[i] = rc[i] = 0;
    cnt = 0;
}

signed main() {
    int T;
    read(T);
    while (T--) {
        init();
        read(n, m);
        for (int i = 1; i <= n; i++) read(p[i]);
        for (int i = 1; i <= n; i++) {
            int top = cnt;
            while (top && p[s[top]] < p[i]) --top;
            if (top) rc[s[top]] = i;
            if (top < cnt) lc[i] = s[top + 1];
            s[cnt = ++top] = i;
        }
        f.resize(n + 1);
        for (int i = 1; i <= n; i++) f[i].resize(m + 1);
        dfs(s[1]);
        writeln(f[s[1]][m]);
    }
    return 0;
}