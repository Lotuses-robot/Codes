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

#define int long long

const int maxn = 5e5 + 10;

int a[maxn];
struct Tree {
    struct Node {
        int l, r, lc, rc,
            ls, rs, sum, ans;
    } nd[maxn << 3];
    int cnt = 0;

    void upd(int u) {
        int lc = nd[u].lc, rc = nd[u].rc;
        nd[u].ls = std::max(nd[lc].ls, nd[lc].sum + nd[rc].ls);
        nd[u].rs = std::max(nd[rc].rs, nd[rc].sum + nd[lc].rs);
        nd[u].sum = nd[lc].sum + nd[rc].sum;
        nd[u].ans = std::max(std::max(nd[lc].ans, nd[rc].ans), nd[lc].rs + nd[rc].ls);
    }

    int bt(int l, int r) {
        int u = ++cnt; auto &p = nd[u];
        p.l = l; p.r = r;
        if (l == r) {
            p.ls = p.rs = p.sum = p.ans = a[l];
        } else {
            int mid = (l + r) >> 1;
            p.lc = bt(l, mid);
            p.rc = bt(mid + 1, r);
            upd(u);
        }
        return u;
    }
    
    void ch(int u, int p, int x) {
        if (nd[u].l == nd[u].r) {
            nd[u].ls = nd[u].rs = nd[u].sum = nd[u].ans = x;
        } else {
            int mid = (nd[u].l + nd[u].r) >> 1;
            if (p <= mid) ch(nd[u].lc, p, x);
            else ch(nd[u].rc, p, x);
            upd(u);
        }
    }

    Node query(int u, int l, int r) {
        if (nd[u].l == l && nd[u].r == r) {
            return nd[u];
        } else {
            int mid = (nd[u].l + nd[u].r) >> 1;
            if (r <= mid) return query(nd[u].lc, l, r);
            else if (l > mid) return query(nd[u].rc, l, r);
            else {
                Node lc = query(nd[u].lc, l, mid), rc = query(nd[u].rc, mid + 1, r);
                nd[cnt + 1] = lc, nd[cnt + 2] = rc;
                nd[0].lc = cnt + 1; nd[0].rc = cnt + 2;
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
    
    int n, q;
    read(n);
    for (int i = 1; i <= n; i++) read(a[i]);
    tr.bt(1, n);
    read(q);
    while (q--) {
        int op, x, y;
        read(op, x, y);
        if (op == 0) {
            tr.ch(1, x, y);
        } else {
            writeln(tr.query(1, x, y).ans);
        }
    }
    return 0;
}