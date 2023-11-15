// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <vector>
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

#define ll long long

const int maxn = 3e6 + 10;
int n, p[maxn], r[maxn];

namespace gen {
    unsigned long long seed;
    unsigned long long rd() {
        seed ^= seed << 13;
        seed ^= seed >> 7;
        seed ^= seed << 17;
        return seed;
    }
}

struct art {
    ll c[maxn];
    int lowbit(int x) { return x & (-x); }
    void add(int x, int y) {
        while (x <= n) {
            c[x] += y;
            x += lowbit(x);
        }
    }
    ll query(int x) {
        ll ans = 0;
        while (x) {
            ans += c[x];
            x -= lowbit(x);
        }
        return ans;
    }
} t1, t2;

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        // freopen(".out", "w", stdout);
    #endif
    
    read(n, gen::seed);

    p[1] = 1;
    for (int i = 2; i <= n; i++) {
        p[i] = i;
        std::swap(p[i], p[gen::rd() % i + 1]);
        // writeln(i, p[i]);
    }
    ll ans = 0, rt;
    for (int i = n; i >= 1; i--) {
        r[p[i]] = i;
        // writeln(i, p[i]);
        rt = t1.query(n - p[i] + 1);
        ans += 1ll * rt * (rt - 1) / 2;
        t1.add(n - p[i] + 1, 1);
    }
    // writeln(ans);
    memset(t1.c, 0, sizeof(t1.c));
    for (int i = 1; i <= n; i++) {
        int f1 = t1.query(r[i]);
        t1.add(r[i], 1);
        ll f2 = t2.query(r[i]);
        t2.add(r[i], f1);
        ans -= f2;
        // writeln(r[i]);
    }
    writeln(ans);
    return 0;
}