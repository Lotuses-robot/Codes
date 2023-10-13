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

const int maxn = 5050;
int cnt[maxn];
int f[maxn][maxn];

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        int n, a;
        read(n);
        memset(cnt, 0, sizeof(cnt[0]) * (n + 10));
        memset(f, 0, sizeof(f[0]) * (n + 10));
        for (int i = 1; i <= n; i++) {
            read(a);
            if (a <= 5000) {
                cnt[a]++;
            }
        }

        int m = 0;
        while (cnt[m] > 0) m++;
        if (m == 0) {
            puts("0");
            continue;
        }
        for (int i = 0; i <= m; i++) f[0][i] = (cnt[0] - 1) * i;
        for (int i = 1; i < m; i++) {
            for (int j = 0; j <= m; j++) {
                f[i][j] = f[0][i];
                // for (int k = 1; k < i; k++) {
                //     f[i][j] = std::min(f[i][j], f[k][i]);
                // }
                f[i][j] += (cnt[i] - 1) * j + i;
                f[0][j] = std::min(f[0][j], f[i][j]);
            }
        }
        // int ans = f[0][m];
        // for (int i = 1; i < m; i++) {
        //     ans = std::min(ans, f[i][m]);
        // }
        writeln(f[0][m]);
    }
    return 0;
}