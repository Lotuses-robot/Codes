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

struct node {
    int x, y;
} val[maxn];

struct Node {
    int x, y, id;
} a[maxn], b[maxn];
int T, n, q, ans1[maxn], ans2[maxn], ans[maxn];

bool operator<(Node x, Node y) {
    if (x.x != y.x)
        return x.x < y.x;
    if (x.y % x.x != y.y % y.x)
        return x.y % x.x < y.y % y.x;
    return x.y < y.y;
}

tsz main() {
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
    read(T);
    while (T--) {
        read(n, q);
        for (int i = 1; i <= q; i++)
            ans1[i] = ans2[i] = 0;
        for (int i = 1; i <= n; i++) {
            read(val[i].x, val[i].y);
        }
        for (int i = 1; i <= q; i++) {
            read(a[i].x, a[i].y);
            b[i].x = a[i].y;
            b[i].y = a[i].x;
            a[i].id = b[i].id = i;
        }
        std::sort(a + 1, a + q + 1);
        std::sort(b + 1, b + q + 1);
        for (int i = 1; i <= n; i++) {
            while (val[i].x && val[i].y) {
                if (val[i].x <= val[i].y) {
                    int t = std::upper_bound(a + 1, a + q + 1, (Node){val[i].x, val[i].y % val[i].x, 0}) - a;
                    int p = std::upper_bound(a + 1, a + q + 1, (Node){val[i].x, val[i].y, 0}) - a;
                    ans1[t]++;
                    ans1[p]--;
                    val[i].y %= val[i].x;
                } else if (val[i].x >= val[i].y) {
                    int t = std::upper_bound(b + 1, b + q + 1, (Node){val[i].y, val[i].x % val[i].y, 0}) - b;
                    int p = std::upper_bound(b + 1, b + q + 1, (Node){val[i].y, val[i].x, 0}) - b;
                    ans2[t]++;
                    ans2[p]--;
                    val[i].x %= val[i].y;
                }
            }
        }
        for (int i = 1; i <= q; i++) {
            ans1[i] += ans1[i - 1];
            ans[a[i].id] = ans1[i];
        }
        for (int i = 1; i <= q; i++) {
            ans2[i] += ans2[i - 1];
            ans[b[i].id] += ans2[i];
        }
        for (int i = 1; i <= q; i++) {
            writeln(ans[i]);
        }
    }
    return 0;
}