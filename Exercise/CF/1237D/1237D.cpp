// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <vector>
// #include <map>
// #include <set>
// #include <forward_list>
// #include <queue>
// #include <stack>
// #include <string>
#include <algorithm>
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

const int maxn = 1e5 + 10;
struct Node {
    int x, id;
    bool operator < (const Node &b) const {
        return x < b.x;
    }
};
Node st[maxn << 2]; int top = -1;
int a[maxn << 2], ans[maxn << 2];

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    int n, max = -1;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
        a[i + 2 * n] = a[i + n] = a[i];
    }
    for (int i = 2 * n; i >= n + 1; i--) {
        while (~top && st[top].x >= a[i] * 2) top--;
        st[++top] = {a[i] * 2, i + 2 * n};
    }
    
    ans[3 * n + 1] = 1e9;
    for (int i = 3 * n; i >= 1; i--) {
        int j = std::lower_bound(st, st + top, (Node){a[i], 0}) - st;
        if (st[j].x >= a[i]) j--;
        ans[i] = ans[i + 1];
        if (j >= 0) {
            ans[i] = std::min(ans[i], st[j].id);
        }
        while (~top && st[top].x >= a[i] * 2) top--;
        st[++top] = {a[i] * 2, i};
    }
    for (int i = 1; i <= n; i++) {
        if (ans[i] - i >= 2 * n) {
            write(-1);
        } else {
            write(ans[i] - i);
        }
        putchar(' ');
    }
    puts("");
    return 0;
}