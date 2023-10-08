// Copyright 2023 Lotuses
#define tsz signed
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

#define ll long long

const int maxn = 1e6 + 10;

int a[maxn];
struct Tree {
    struct Node {
        int l, r, lc, rc;
        ll lt, rt; bool anc;
        ll lazy;
    } nd[maxn << 2];
    int cnt;

    void init() {
        cnt = 0;
    }

    void upd(int u) {
        int lc = nd[u].lc, rc = nd[u].rc;
        nd[u].lt = nd[lc].lt;
        nd[u].rt = nd[rc].rt;
        nd[u].anc = nd[lc].anc && nd[rc].anc && (nd[lc].rt <= nd[rc].lt);
    }

    void pushd(int u) {
        if (!nd[u].lazy) return;
        int lc = nd[u].lc, rc = nd[u].rc;
        if (~lc) {
            nd[lc].lt += nd[u].lazy;
            nd[lc].rt += nd[u].lazy;
            nd[lc].lazy += nd[u].lazy;
        }
        if (~rc) {
            nd[rc].lt += nd[u].lazy;
            nd[rc].rt += nd[u].lazy;
            nd[rc].lazy += nd[u].lazy;
        }
        nd[u].lazy = 0;
    }

    int bt(int l, int r) {
        int u = ++cnt;
        nd[u].l = l; nd[u].r = r;
        nd[u].lt = a[l]; nd[u].rt = a[r];
        nd[u].lc = nd[u].rc = -1;
        if (l == r) {
            nd[u].anc = true;
        } else {
            int mid = (l + r) >> 1;
            nd[u].lc = bt(l, mid);
            nd[u].rc = bt(mid + 1, r);
            upd(u);
        }
        return u;
    }

    void add(int u, int l, int r, int x) {
        if (nd[u].l == l && nd[u].r == r) {
            nd[u].lt += x;
            nd[u].rt += x;
            nd[u].lazy += x;
        } else {
            pushd(u);
            int mid = (nd[u].l + nd[u].r) >> 1;
            if (r <= mid) add(nd[u].lc, l, r, x);
            else if (l > mid) add(nd[u].rc, l, r, x);
            else {
                add(nd[u].lc, l, mid, x);
                add(nd[u].rc, mid + 1, r, x);
            }
            upd(u);
        }
    }

    Node query(int u, int l, int r) {
        if (nd[u].l == l && nd[u].r == r) {
            return nd[u];
        } else {
            pushd(u);
            int mid = (nd[u].l + nd[u].r) >> 1;
            if (r <= mid) return query(nd[u].lc, l, r);
            else if (l > mid) return query(nd[u].rc, l, r);
            else {
                Node lc = query(nd[u].lc, l, mid), rc = query(nd[u].rc, mid + 1, r);
                nd[cnt + 1] = lc; nd[cnt + 2] = rc;
                nd[0] = {l, r, cnt + 1, cnt + 2};
                nd[0].lc = cnt + 1;
                nd[0].rc = cnt + 2;
                upd(0);
                return nd[0];
            }
        }
    }
} tr;

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, k;
    read(n, k);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    tr.init(); tr.bt(1, n);
    while (k--) {
        int op, x, y, z;
        read(op, x, y);
        if (y > n) y = n;
        switch(op) {
            case 1: 
                read(z);
                tr.add(1, x, y, z);
                break;
            case 2:
                puts(tr.query(1, x, y).anc ? "Yes" : "No");
                break;
        }
    }
    return 0;
}