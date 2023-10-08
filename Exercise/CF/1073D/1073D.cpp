// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
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
#define debug(arg, args...) { printf("db <%d> ", __LINE__); writeln(arg, ##args); }
#else
#define debug(arg, args...) {}
#endif

#define int long long

const int maxn = 2e5 + 10;
int a[maxn];

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    int n, t, s = 0, cnt = 0, ans = 0;
    read(n, t);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
        if (a[i] <= t - s) {
            s += a[i];
            cnt++;
        }
    }
    while (t > 0 && s > 0) {
        ans += t / s * cnt;
        t %= s;
        s = 0; cnt = 0;
        for (int i = 1; i <= n; i++) {
            if (a[i] <= t - s) {
                s += a[i];
                cnt++;
            }
        }
    }
    writeln(ans);
    return 0;
}