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

const int maxn = 3e5 + 10;
int ans, a[maxn], b[maxn];

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    int n, k, psum = 0, pans = 0;
    read(n, k);
    for (int i = 1; i <= n; i++) read(b[i]);
    for (int i = n; i >= k; i--) {
        pans -= psum;
        if (i + k <= n) {
            psum -= a[i + k];
        }
        if (pans < b[i]) {
            a[i] = (b[i] - pans) / k + ((b[i] - pans) % k > 0);
            psum += a[i];
            pans += a[i] * k;
            ans += a[i];
        }
        // write(a[i]); putchar(' ');
    }
    int mx = 0;
    for (int i = k - 1; i >= 1; i--) {
        pans -= psum;
        if (i + k <= n) {
            psum -= a[i + k];
        }
        if (pans < b[i]) {
            mx = std::max(mx, (b[i] - pans) / i + ((b[i] - pans) % i > 0));
        }
    }
    // writeln(mx);
    // puts("");
    writeln(ans + mx);
    return 0;
}