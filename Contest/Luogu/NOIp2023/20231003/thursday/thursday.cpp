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

const int maxn = 50005, mod = 1e9 + 7;
int f[520][maxn];

void init() {
    f[0][0] = 1;
    for (int i = 1; i <= 500; i++) {
        for (int j = 0; j <= 50000; j++) {
            f[i][j] = (f[i - 1][j] + ((j >= i) ? f[i - 1][j - i] : 0)) % mod;
        }
    }
    for (int i = 1; i <= 500; i++) {
        for (int j = 1; j <= 50000; j++) {
            f[i][j] += f[i][j - 1];
            f[i][j] %= mod;
            // write(f[i][j]); putchar(' ');
        }
        // puts("");
    }
}

tsz main() {
    freopen("thursday.in", "r", stdin);
    freopen("thursday.out", "w", stdout);
    
    init();
    int T;
    read(T);
    while (T--) {
        int n, m, ans = 0;
        read(n, m);
        for (int i = 1; i <= 500; i++) {
            int l = (i + 1) * i / 2 - m, r = n;
            // writeln(l, r);
            if (l > r) break; 
            ans += ((f[i][r] - (l - 1 >= 0 ? f[i][l - 1] : 0)) % mod + mod) % mod;
            ans %= mod;
        }
        writeln(ans);
    }
    return 0;
}