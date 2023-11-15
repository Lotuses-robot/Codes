// Copyright 2023 Lotuses
#define tsz signed
#include <cmath>
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

#define int long long

const int maxn = 2e5 + 10;
int a[maxn];

struct Tree {
    struct Node {
        int l, r, lc, rc;
        double coss, sins;
        int lazy;
    } nd[maxn << 3];
    int cnt;

    Tree() { cnt = 0; }

    void upd(int u) {
        int lc = nd[u].lc, rc = nd[u].rc;
        nd[u].sins = nd[lc].sins + nd[rc].sins;
        nd[u].coss = nd[lc].coss + nd[rc].coss;
    }

    void c(int u, double sinx, double cosx) {
        double coss = nd[u].coss, sins = nd[u].sins;
        nd[u].sins = sins * cosx + sinx * coss;
        nd[u].coss = coss * cosx - sins * sinx;
    }

    void pushd(int u) {
        if (nd[u].lazy) {
            int lc = nd[u].lc, rc = nd[u].rc;
            double si = sinl(nd[u].lazy), co = cosl(nd[u].lazy);
            c(lc, si, co);
            c(rc, si, co);
            nd[lc].lazy += nd[u].lazy;
            nd[rc].lazy += nd[u].lazy;
            nd[u].lazy = 0;
        }
    }

    int bt(int l, int r) {
        int u = ++cnt;
        nd[u].l = l; nd[u].r = r;
        nd[u].lc = nd[u].rc = -1; nd[u].lazy = 0;
        if (l == r) {
            nd[u].sins = sinl(a[l]);
            nd[u].coss = cosl(a[l]);
        } else {
            int mid = (l + r) >> 1;
            nd[u].lc = bt(l, mid);
            nd[u].rc = bt(mid + 1, r);
            upd(u);
        }
        return u;
    }

    void ch(int u, int l, int r, int x) {
        if (nd[u].l == l && nd[u].r == r) {
            nd[u].lazy += x;
            double si = sinl(x), co = cosl(x);
            c(u, si, co);
        } else {
            pushd(u);
            int mid = (nd[u].l + nd[u].r) >> 1;
            if (r <= mid) ch(nd[u].lc, l, r, x);
            else if (l > mid) ch(nd[u].rc, l, r, x);
            else ch(nd[u].lc, l, mid, x), ch(nd[u].rc, mid + 1, r, x);
            upd(u);
        }
    }

    double query(int u, int l, int r) {
        if (nd[u].l == l && nd[u].r == r) {
            return nd[u].sins;
        } else {
            pushd(u);
            int mid = (nd[u].l + nd[u].r) >> 1;
            if (r <= mid) return query(nd[u].lc, l, r);
            else if (l > mid) return query(nd[u].rc, l, r);
            else return query(nd[u].lc, l, mid) + query(nd[u].rc, mid + 1, r);
        }
    }
} tr;

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    tr.bt(1, n);
    int T;
    read(T);
    while (T--) {
        int op, x, y, z;
        read(op, x, y);
        if (op == 1) {
            read(z);
            tr.ch(1, x, y, z);
        } else {
            printf("%.1lf\n", tr.query(1, x, y));
        }
    }
    return 0;
}