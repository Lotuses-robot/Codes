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

#define int long long

const int maxn = 1e6 + 10;
const int inf = 0x7f7f7f7f7f7f7f7;
int a[maxn], b[maxn];

struct Tree {
    #define max(a, b) ((a) > (b) ? (a) : (b))
    #define min(a, b) ((a) < (b) ? (a) : (b))

    struct Node {
        int l, r, lc, rc;
        int ans, ansl, ansr, maxA, minB;
    } nd[maxn << 2];
    int cnt;

    void fixup(int u) {
        int lc = nd[u].lc, rc = nd[u].rc;
        nd[u].maxA = max(nd[lc].maxA, nd[rc].maxA);
        nd[u].minB = min(nd[lc].minB, nd[rc].minB);
        int dist = nd[u].r - nd[u].l + 1;
        nd[u].ansl = nd[u].ansr = nd[u].ans = -inf;
        if (dist >= 2) {
            nd[u].ansl = max(nd[lc].maxA - nd[rc].minB, max(nd[lc].ansl, nd[rc].ansl));
            nd[u].ansr = max(nd[rc].maxA - nd[lc].minB, max(nd[lc].ansr, nd[rc].ansr));
        }
        if (dist >= 3) {
            nd[u].ans = max(max(nd[lc].ansl + nd[rc].maxA, nd[rc].ansr + nd[lc].maxA),
                            max(nd[lc].ans, nd[rc].ans));
        }
    }

    int bt(int l, int r) {
        int id = ++cnt;
        nd[id].l = l; nd[id].r = r;
        nd[id].ans = nd[id].ansl = nd[id].ansr = -inf;
        if (l == r) {
            nd[id].lc = nd[id].rc = -1;
            nd[id].maxA = a[l]; nd[id].minB = b[l];
        } else {
            int mid = (l + r) >> 1;
            nd[id].lc = bt(l, mid);
            nd[id].rc = bt(mid + 1, r);
            fixup(id);
        }
        return id;
    }

    void chA(int u, int p, int c) {
        if (nd[u].l == p && nd[u].r == p) {
            nd[u].maxA = c;
        } else {
            int mid = (nd[u].l + nd[u].r) >> 1;
            if (p <= mid) {
                chA(nd[u].lc, p, c);
            } else {
                chA(nd[u].rc, p, c);
            }
            fixup(u);
        }
    }

    void chB(int u, int p, int c) {
        if (nd[u].l == p && nd[u].r == p) {
            nd[u].minB = c;
        } else {
            int mid = (nd[u].l + nd[u].r) >> 1;
            if (p <= mid) {
                chB(nd[u].lc, p, c);
            } else {
                chB(nd[u].rc, p, c);
            }
            fixup(u);
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
                Node a = query(nd[u].lc, l, mid),
                     b = query(nd[u].rc, mid + 1, r);
                nd[cnt + 1] = a;
                nd[cnt + 2] = b;
                nd[0].lc = cnt + 1; nd[0].rc = cnt + 2;
                nd[0].l = l; nd[0].r = r;
                fixup(0);
                return nd[0];
            }
        }
    }
} tr;

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, m;
    read(n, m);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    for (int i = 1; i <= n; i++) {
        read(b[i]);
    }
    tr.bt(1, n);
    while (m--) {
        int ch, x, y;
        read(ch, x, y);
        if (ch == 1) {
            tr.chA(1, x, y);
        } else if (ch == 2) {
            tr.chB(1, x, y);
        } else {
            writeln(tr.query(1, x, y).ans);
        }
    }
    return 0;
}
