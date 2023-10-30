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

const int maxn = 3e5 + 10, mod = 998244353;
int n;
int b[maxn][30];
int a[maxn];

int calc(int p) {
    int s[2] = {}, c[2] = {}, prv = 0, ans = 0;
    for (int i = 1; i <= n; i++) {
        prv ^= b[i][p];
        ans += (((i + 1) * c[prv ^ 1] % mod - s[prv ^ 1] % mod) % mod + mod) % mod;
        // printf("ans ");
        // writeln((i + 1) * c[prv ^ 1] - s[prv ^ 1], b[i][p]);
        ans += b[i][p];
        ans %= mod;
        (s[prv ^ b[i][p]] += i) %= mod;
        c[prv ^ b[i][p]]++;
        // writeln(s[0], s[1], c[0], c[1]);
    }
    return ans;
}

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
        for (int j = 0; j < 30; j++) {
            b[i][j] = (a[i] & (1ll << j)) > 0;
        }
    }
    int ans = 0;
    for (int p = 0; p < 30; p++) {
        // writeln(calc(p));
        ans += (1ll << p) * calc(p) % mod;
        ans %= mod;
    }
    writeln(ans);
    return 0;
}