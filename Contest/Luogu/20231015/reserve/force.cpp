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

const int maxn = 5e5 + 10;
int a[maxn], b[maxn], c[maxn], p[maxn];

tsz main() {
    #ifdef LOCAL
        freopen("data/reserve8.in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, q;
    read(n);
    for (int i = 1; i <= n; i++) read(a[i]);
    for (int i = 1; i <= n; i++) read(b[i]);
    for (int i = 1; i <= n; i++) read(c[i]);
    read(q);
    while (q--) {
        int m, pans, ans = 0;
        read(m);
        for (int i = 1; i <= m; i++) {
            read(p[i]);
        }
        for (int i = m + 1; i <= n; i++) p[i] = 0;
        for (int i = 1, j = 1; i <= n; i++) {
            if (i == p[j]) { j++; continue; }
            ans += b[i];
        }
        pans = ans;
        for (int i = 1, j = 1; i <= n; i++) {
            if (i == p[j]) {
                ans += c[i];
                j++;
            } else {
                ans -= b[i];
            }
            pans = std::min(pans, ans + a[i]);
        }
        writeln(pans);
    }
    return 0;
}