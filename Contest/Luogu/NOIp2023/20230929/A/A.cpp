// Copyright 2023 Lotuses
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

const int maxn = 4e6 + 10;
int n;
int a[maxn], b[maxn], f[maxn], c[maxn];
std::vector<int> v;

int lowbit(int x) {
    return x & (-x);
}

void ch(int x, int k) {
    if (x == 0) return;
    while (x <= n) {
        c[x] = std::max(k, c[x]);
        x = x + lowbit(x);
    }
}

int getsum(int x) {
    int ans = 0;
    while (x > 0) {
        ans = std::max(ans, c[x]);
        x = x - lowbit(x);
    }
    return ans;
}

int mp1(int x) {
    return std::lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
}

int mp2(int x) {
    return std::upper_bound(v.begin(), v.end(), x) - v.begin() + 1;
}

int mx = 0;

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
        v.push_back(a[i]);
        mx = std::max(mx, a[i]);
    }
    for (int i = 1; i <= n; i++) {
        read(b[i]);
        f[i] = 1;
    }

    std::sort(v.begin(), v.end());

    int ans = f[1];
    ch(mp2(a[1] * b[f[1]]), f[1]);
    for (int i = 2; i <= n; i++) {
        // writeln(a[i], mp(a[i]), getsum(mp(a[i])));
        f[i] = std::max(f[i], getsum(mp1(a[i])) + 1);
        ans = std::max(ans, f[i]);

        if (a[i] * b[f[i]] > mx) continue;

        ch(mp2(a[i] * b[f[i]]), f[i]);
        // printf("ins %lld %lld\n", mp(a[i] * b[f[i]]), f[i]);
    }
    writeln(ans);
    return 0;
}
