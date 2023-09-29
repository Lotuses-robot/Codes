// Copyright 2023 Lotuses
#include <cstdio>
#include <ctime>
#include <cstring>
#include <vector>
#include <algorithm>

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
#define debug(arg, args...) { printf("d <%d> ", __LINE__); writeln(arg, ##args); }
#else
#define debug(arg, args...) {}
#endif

const int maxn = 200, mod = 10;
int a[maxn], s[maxn], sa;
int n, m;
int ansmax = 0, ansmin = 1e9;
int bg;

void dfs(int p, int now, int ans) {
    if (clock() - bg >= CLOCKS_PER_SEC * 0.999) return;
    if (p < m && now > n) return;
    int sum = 0;
    if (p == m) {
        for (int i = now; i <= n; i++) sum += a[i];
        ansmax = std::max(ansmax, ans * (sum % mod));
        ansmin = std::min(ansmin, ans * (sum % mod));
        return;
    }
    for (int c = now; c <= n - 1; c++) {
        sum += a[c];
        dfs(p + 1, c + 1, ans * (sum % mod));
    }
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    bg = clock();
    read(n, m);
    for (int i = 1; i <= n; i++) {
        read(a[i]); a[i] = (a[i] % mod + mod) % mod;
        a[i + n] = a[i];
    }
    sa = s[n];
    for (int i = 1; i <= n; i++) {
        dfs(1, 1, 1);
        for (int j = 1; j <= 2 * n; j++) a[j] = a[j + 1];
    }
    writeln(ansmin);writeln(ansmax);
    return 0;
}
