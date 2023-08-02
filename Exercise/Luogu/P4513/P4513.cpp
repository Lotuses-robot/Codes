// Copyright 2023 Lotuses
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

#define max(a, b) ((a) > (b) ? (a) : (b))

const int maxn = 5e5 + 10;
int a[maxn];
struct Tree {
    struct Node {
        int l, r, lc, rc;
        int ansl, ansr, ans, sum;
    } nd[maxn << 2];
    int cnt = 0;

    void init() {
        memset(nd, 0, sizeof(nd)); cnt = 0;
    }

    void fixup(int u) {
        static int lc, rc;
        lc = nd[u].lc; rc = nd[u].rc;
        nd[u].sum = nd[lc].sum + nd[rc].sum;
        nd[u].ansl = max(nd[lc].ansl, nd[lc].sum + nd[rc].ansl);
        nd[u].ansr = max(nd[rc].ansr, nd[rc].sum + nd[lc].ansr);
        nd[u].ans = max(nd[lc].ansr + nd[rc].ansl, max(nd[lc].ans, nd[rc].ans));
    }

    int bt(int l, int r) {
        int id = ++cnt;
        nd[id].l = l; nd[id].r = r;
        if (l == r) {
            nd[id].ansl = nd[id].ansr = nd[id].ans = nd[id].sum = a[l];
            nd[id].lc = nd[id].rc = -1;
        } else {
            int mid = (l + r) >> 1;
            nd[id].lc = bt(l, mid);
            nd[id].rc = bt(mid + 1, r);
            fixup(id);
        }
        return id;
    }

    void change(int u, int pt, int c) {
        if (nd[u].l == pt && nd[u].r == pt) {
            nd[u].ans = nd[u].ansl = nd[u].ansr = nd[u].sum = c;
        } else {
            int mid = (nd[u].l + nd[u].r) >> 1;
            if (pt <= mid) {
                change(nd[u].lc, pt, c);
            } else {
                change(nd[u].rc, pt, c);
            }
            fixup(u);
        }
    }

    Node query(int u, int l, int r) {
        if (nd[u].l == l && nd[u].r == r) {
            return nd[u];
        } else {
            int mid = (nd[u].l + nd[u].r) >> 1;
            if (r <= mid) {
                return query(nd[u].lc, l, r);
            } else if (l > mid) {
                return query(nd[u].rc, l, r);
            } else {
                Node a = query(nd[u].lc, l, mid), b = query(nd[u].rc, mid + 1, r);
                nd[cnt + 1] = a;
                nd[cnt + 2] = b;
                nd[0].lc = cnt + 1;
                nd[0].rc = cnt + 2;
                fixup(0);
                return nd[0];
            }
        }
    }
} tr;

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, m;
    read(n, m);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    tr.bt(1, n);
    for (int i = 1; i <= m; i++) {
        int c, a, b;
        read(c, a, b);
        if (c == 1) {
            if (a > b) std::swap(a, b);
            writeln(tr.query(1, a, b).ans);
        } else {
            tr.change(1, a, b);
        }
    }
    return 0;
}
