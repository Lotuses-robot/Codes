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

const int maxn = 3e5 + 10;
int n, m;
int a[maxn];

bool check(int c) {
    int ans = 0;
    for (int i = 1; i <= m; i++) {
        ans += a[i] / c + (a[i] % c > 0);
    }
    return ans <= n;
}

signed main() {
    #ifdef LOCAL
        freopen("data/frog5.in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, m);
    for (int i = 1; i <= m; i++) {
        read(a[i]);
    }

    int l = 1, r = 1e9;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    if (check(l)) writeln(l);
    else if (check(l + 1)) writeln(l + 1);
    else writeln(r);
    return 0;
}
