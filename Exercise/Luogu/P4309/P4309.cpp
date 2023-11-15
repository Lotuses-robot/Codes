// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
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

const int maxn = 1e6 + 10;
int tr[maxn], ans[maxn], n;
std::vector<int> a;
#define lowbit(x) ((x) & (-(x)))
void add(int x, int val) {
    while (x <= n) {
        tr[x] = std::max(tr[x], val);
        x += lowbit(x);
    }
}
int query(int x) {
    int ret = 0;
    while (x > 0) {
        ret = std::max(ret, tr[x]);
        x -= lowbit(x);
    }
    return ret;
}

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    int x;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(x);
        a.insert(a.begin() + x, i);
    }
    for (auto x : a) {
        add(x, ans[x] = query(x) + 1);
    }
    for (int i = 1; i <= n; i++) {
        ans[i] = std::max(ans[i], ans[i - 1]);
        writeln(ans[i]);
    }
    return 0;
}