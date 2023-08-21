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

const int maxn = 2e5, mod = 998244353;

int n, m, k;
int fc[maxn + 10], inv[maxn + 10];
int cz[maxn + 10];

void ex_gcd(int cz, int b, int &x, int &y) {
    if (b == 0) x = 1, y = 0;
    else ex_gcd(b, cz % b, y, x), y -= cz / b * x;
}

void init() {
    fc[0] = inv[0] = 1;
    for (int i = 1, gmax; i <= maxn; i++) {
        fc[i] = fc[i - 1] * i % mod;
        ex_gcd(fc[i], mod, inv[i], gmax),
        inv[i] = (inv[i] + mod) % mod;
        ex_gcd(i, mod, cz[i], gmax);
        cz[i] = (cz[i] + mod) % mod;
    }
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    init();
    int T;
    read(T);
    while (T--) {
        read(n, m, k);
        int ans = 0;
        for (int i = 0; i < k; i++) {
            // int inv, ff;
            ans = (ans + cz[n - i] * (n - k) % mod * fc[k] % mod * fc[n - i] % mod * inv[n] % mod * inv[k - i] % mod * (k - i) % mod) % mod;
        }
        writeln((ans * m % mod + n) % mod);
    }
    return 0;
}