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
char ch[maxn], c[maxn];

int qpow(int x, int y) {
    int base = x; x = 1;
    do {
        if (y & 1) x = x * base % mod;
        base = base * base % mod;
    } while (y >>= 1);
    return x;
}

int inv(int x) {
    return qpow(x, mod - 2);
}

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    int n, m, ans2 = 1, ans = 1;
    read(n, m);
    scanf("%s", ch + 2);

    if (ch[2] == '?') ans2 = 0;
    for (int i = 3; i <= n; i++) {
        if (ch[i] == '?') {
            ans *= (i - 2);
            ans %= mod;
        }
    }

    writeln(ans2 * ans % mod);

    for (int i = 1; i <= m; i++) {
        int x;
        read(x); x++;
        scanf("%s", c);
        if (x == 2) {
            if (c[0] == '?') {
                ans2 = 0;
            } else {
                ans2 = 1;
            }
        } else {
            if (c[0] == '?') {
                if (ch[x] == '<' || ch[x] == '>') {
                    ans = ans * (x - 2) % mod;
                }
            } else {
                if (ch[x] == '?') {
                    // writeln(ans, x - 2, inv(x - 2));
                    ans = ans * inv(x - 2) % mod;
                }
            }
        }
        ch[x] = c[0];
        writeln(ans * ans2 % mod);
    }
    return 0;
}