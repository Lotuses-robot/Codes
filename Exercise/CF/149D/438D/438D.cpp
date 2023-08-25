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

const int maxn = 1e5 + 5;
struct Tree {
    struct Node {
        int l, r, lc, rc;
        int _max, _sum;
    } nd[maxn << 4];
    int a[maxn];
    int cnt;
    
    void upd(int u) {
        Node &e = nd[u]; Node &lc = nd[e.lc], &rc = nd[e.rc];
        e._sum = lc._sum + rc._sum;
        e._max = std::max(lc._max, rc._max);
    }

    int bt(int l, int r) {
        int id = ++cnt;
        Node &e = nd[id];
        e.l = l; e.r = r;
        if (l == r) {
            e._max = e._sum = a[l];
        } else {
            int mid = (l + r) >> 1;
            e.lc = bt(l, mid);
            e.rc = bt(mid + 1, r);
            upd(id);
        }
        return id;
    }

    void ch(int id, int x, int c) {
        Node &e = nd[id];
        if (e.l == x && e.r == x) {
            e._max = e._sum = c;
        } else {
            int mid = (e.l + e.r) >> 1;
            if (x <= mid) ch(e.lc, x, c);
            else ch(e.rc, x, c);
            upd(id);
        }
    }

    void mod(int id, int l, int r, int c) {
        Node &e = nd[id];
        if (e._max < c) return;
        if (e.l == e.r) {
            e._max %= c;
            e._sum %= c;
        } else {
            int mid = (e.l + e.r) >> 1;
            if (r <= mid) mod(e.lc, l, r, c);
            else if (l > mid) mod(e.rc, l, r, c);
            else {
                mod(e.lc, l, mid, c);
                mod(e.rc, mid + 1, r, c);
            }
            upd(id);
        }
    }

    int query(int id, int l, int r) {
        Node &e = nd[id];
        if (e.l == l && e.r == r) {
            return e._sum;
        } else {
            int mid = (e.l + e.r) >> 1;
            if (r <= mid) return query(e.lc, l, r);
            else if (l > mid) return query(e.rc, l, r);
            else {
                return query(e.lc, l, mid) + query(e.rc, mid + 1, r);
            }
        }
    }
} tr;

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, q;
    read(n, q);
    for (int i = 1; i <= n; i++) {
        read(tr.a[i]);
    }
    tr.bt(1, n);
    while (q--) {
        int ch, x, y;
        read(ch, x, y);
        if (ch == 1) {
            writeln(tr.query(1, x, y));
        } else if (ch == 2) {
            int c;
            read(c);
            tr.mod(1, x, y, c);
        } else {
            tr.ch(1, x, y);
        }
    }
    return 0;
}
