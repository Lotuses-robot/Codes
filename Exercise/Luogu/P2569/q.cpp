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
const int maxn = 1e6 + 5;
const int mod = 998244353;
int b[maxn];
int a[maxn];
int cnt[maxn];
int w = 0;

int find(int l, int r) {
    for (int i = l; i <= r; i++) {
        cnt[a[i]]++;
    }
    int maxx = 0, maxid = 0;
    for (int i = 1; i <= 1000; i++) {
        if (cnt[i] > maxx) {
            maxx = cnt[i];
            maxid = i;
        }
        cnt[i] = 0;
    }
    return maxid;
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n;
    read(n);

    // if (n == 2) {
    //     int a, b, ans = 0;
    //     read(a, b);
    //     for (int i = 1; i <= a; i++) {
    //         if (b >= i) {
    //             ans += i * (a - i + 1) % mod + (i - 1) * 1 % mod + (b - i + 1) * i % mod;
    //             ans %= mod;
    //         } else {
    //             ans += i * (a - i + 1) % mod + b * 1;
    //             ans %= mod;
    //         }
    //         // writeln(ans);
    //     }
    //     for (int i = 1; i <= b; i++) {
    //         ans += i * (b - i + 1) % mod;
    //         ans %= mod;
    //     }
    //     writeln(ans);
    //     return 0;
    // }

    for (int i = 1; i <= n; i++) {
        read(b[i]);
    }

    int ans = 0;
    for (int i = 1; i <= 1000; i++) {
        int ans1 = 0;
        for (int j = n; j >= 1; j--) {
            if (b[j] >= i) {
                ans1 += i * (b[j] - )
            }
            writeln(i, j, ans, ans1);
        }
    }
    writeln(ans);
    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j <= b[i]; j++) {
    //         a[++w] = j;
    //     }
    // }

    // int ans = 0;
    // for (int i = 1; i <= w; i++) {
    //     for (int j = i; j <= w; j++) {
    //         ans += find(i, j);
    //     }
    // }
    // writeln(ans);
    return 0;
}
