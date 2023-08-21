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

const int mod = 1e9 + 7;

char ch[100];
int len = 0;
int f[20];
int pow10[20];

int dfs(int u, bool full, int num) {
    if (u == len + 1) return 0;
    if (!full && f[u]) return f[u];
    int up = full ? ch[u] - '0' : 9;
    int ans;
    if (full) {
        if (up == 0) ans = 0;
        else ans = up * (up - 1) / 2 % mod * pow10[len - u] % mod + (num % pow10[len - u] + 1) * up % mod;
        ans %= mod;
        ans += dfs(u + 1, true, num % pow10[len - u]); ans %= mod;
        ans += dfs(u + 1, false, num % pow10[len - u]) * up % mod; ans %= mod;
    } else {
        ans = up * (up + 1) / 2 % mod * pow10[len - u] % mod;
        ans += dfs(u + 1, false, num % pow10[len - u]) * 10 % mod; ans %= mod;
    }
    if (!full) return f[u] = ans;
    return ans;
}

int calc(int x) {
    sprintf(ch + 1, "%lld", x);
    len = strlen(ch + 1);
    memset(f, 0, sizeof(f));
    return dfs(1, true, x);
}

void init() {
    pow10[0] = 1;
    for (int i = 1; i <= 18; i++) {
        pow10[i] = pow10[i - 1] * 10;
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
        int l, r;
        read(l, r);
        writeln(((calc(r) - calc(l - 1)) % mod + mod) % mod);
    }
    return 0;
}
