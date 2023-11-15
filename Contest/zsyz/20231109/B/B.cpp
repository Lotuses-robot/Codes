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

// #define int long long
#define ll long long

const int maxn = 5e5 + 10;
int n, m, k, d;
template<typename T>
T max(T a, T b) { return a > b ? a : b; }
struct Tree {
    struct Node {
        int l, r, lc, rc;
        ll sum, max, ls, rs;
    } nd[maxn << 2];
    int cnt;

    Tree(): cnt(0) {}

    void upd(int u) {
        static int lc, rc;
        lc = nd[u].lc, rc = nd[u].rc;
        nd[u].sum = nd[lc].sum + nd[rc].sum;
        nd[u].ls = max(0ll, max(nd[lc].ls, nd[lc].sum + nd[rc].ls));
        nd[u].rs = max(0ll, max(nd[rc].rs, nd[rc].sum + nd[lc].rs));
        nd[u].max = max(0ll, max(max(nd[lc].max, nd[rc].max), nd[lc].rs + nd[rc].ls));
    }

    int bt(int l, int r) {
        int u = ++cnt;
        nd[u].l = l; nd[u].r = r;
        nd[u].lc = nd[u].rc = -1;
        if (l == r) {
            nd[u].sum = -k;
            nd[u].max = nd[u].ls = nd[u].rs = 0;
        } else {
            int mid = (l + r) >> 1;
            nd[u].lc = bt(l, mid);
            nd[u].rc = bt(mid + 1, r);
            upd(u);
        }
        return u;
    }
    void add(int u, int x, int y) {
        if (nd[u].l == nd[u].r) {
            nd[u].sum += y;
            nd[u].ls = nd[u].rs = nd[u].max = max(0ll, nd[u].sum);
        } else {
            int mid = (nd[u].l + nd[u].r) >> 1;
            if (x <= mid) add(nd[u].lc, x, y);
            else add(nd[u].rc, x, y);
            upd(u);
        }
    }
} tr;

tsz main() {
    // #ifdef LOCAL
    //     freopen(".in", "r", stdin);
    //     freopen(".out", "w", stdout);
    // #endif
    // freopen("B.in", "r", stdin);
    // freopen("B.out", "w", stdout);

    read(n, m, k, d);
    tr.bt(1, n);
    for (int i = 1; i <= m; i++) {
        static int x, y;
        read(x, y);
        tr.add(1, x, y);
        if (tr.nd[1].max <= 1ll * k * d) {
            puts("YES");
        } else {
            puts("NO");
        }
    }
    return 0;
}