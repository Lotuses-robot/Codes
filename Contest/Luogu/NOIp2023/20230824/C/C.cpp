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

#define ceil(a, b) (((a) % (b) == 0 ? ((a) / (b)) : ((a) / (b) + 1)))

const int maxn = 1e5 + 10;
int f[maxn], a, b;
int dfs(int u) {
    // writeln(u);
    if (u <= 1) return 0;
    if (f[u]) return f[u];
    int ans = u * a + b;
    for (int k = u; k >= 2; k = ceil(u, ceil(u, k)) - 1) {
        // writeln(u, ceil(u, k), ceil(u, ceil(u, k)));
        ans = std::min(ans, dfs(ceil(u, k)) + (ceil(u, ceil(u, k)) - 1) * a + b);
    }
    // writeln(u, ans);
    return f[u] = ans;
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        memset(f, 0, sizeof(f));
        int n;
        read(n, a, b);
        if (n == 1) { puts("0"); continue; }
        if (n <= 1e3 + 10) {
            writeln(dfs(n));
            continue;
        }
        
        int ans = (n - 1) * a + b;
        int t, p, s;
        for (int i = 2; i * i <= n; i++) {
            t = 1; s = 0;
            while (t * i <= n)
            {
                s += a * (i - 1) + b; t *= i;
                if (n % t) p = n / t + 1;
                else p = n / t;
                if (p != 1) ans = std::min(ans, s + a * (p - 1) + b);
            }
        }
        writeln(ans);
    }
    return 0;
}
