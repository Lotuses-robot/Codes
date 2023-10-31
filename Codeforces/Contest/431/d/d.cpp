// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <vector>
#include <bitset>
// #include <map>
// #include <set>
// #include <list>
// #include <queue>
// #include <stack>
// #include <string>
// #include <algorithm>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

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
#define ins(a, b) (G[a].emplace_back(b))

#define int unsigned long long

int f[128][128];
std::bitset<128> b;

int dfs(int u, int ct, bool ful) {
    if (ct >= 128 || u >= 128) return 0;
    if (!ful && ~f[u][ct]) return f[u][ct];
    int ans = 0, lmt = 2;
    if (u == 0) {
        if (ful) ans = ct <= b.test(u);
        else ans = ct <= 1;
        // ans = ct <= ;
        goto ret;
    }
    if (ful) {
        ans += dfs(u - 1, ct - b.test(u), true);
        lmt = b.test(u);
    }
    for (int i = 0; i < lmt; i++) {
        ans += dfs(u - 1, ct - i, false);
    }
    ret: if (!ful) f[u][ct] = ans;
    return ans;
}

int getans(int x, int k) {
    memset(f, -1, sizeof(f));
    b = x;
    return dfs(63, k, true);    
}

int calc(int n, int k) {
    // [n + 1, 2 * n]
    // writeln(getans(2 * n, k), getans(n, k));
    return getans(2 * n, k) - getans(n, k);
}

int m, k;
bool check(int x) {
    // writeln(x, k, calc(x, k));
    return calc(x, k) >= m;
}

tsz main() {
    #ifdef LOCAL
        // freopen(".in", "r", stdin);
        // freopen(".out", "w", stdout);
    #endif
    
    // writeln(calc(5, 3));

    read(m, k);
    int l = 1, r = 1e18;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
        // writeln(l, r);
    }
    writeln(r);
    return 0;
}