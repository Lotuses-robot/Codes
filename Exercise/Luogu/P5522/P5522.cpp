// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <vector>
#include <bitset>

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

const int maxn = 1e5 + 10;
int n, m, q;
char ch[50];
struct val {
    std::bitset<30> s[2];
    int cnt = 0;
    val operator & (val b) const {
        val a = *this;
        if (!(~a.cnt) || !(~b.cnt)) {
            a.cnt = -1;
            return a;
        }
        a.cnt = 0;
        for (int i = 0; i < n; i++) {
            if (a.s[1][i] && b.s[1][i]) {
                a.cnt++;
            } else if (a.s[1][i]) {
                a.s[1][i] = 0;
                a.s[0][i] = b.s[0][i];
            } else if (b.s[1][i]) {
            } else {
                if (a.s[0][i] ^ b.s[0][i]) {
                    a.cnt = -1;
                    return a;
                }
            }
        }
        return a;
    }

    void print() const {
        for (int i = 0; i < n; i++) {
            putchar('0' + s[0][i]);
        } puts("");
        for (int i = 0; i < n; i++) {
            putchar('0' + s[1][i]);
        } puts("");
    }
} a[maxn];

struct Tree {
    struct Node {
        int l, r, lc, rc;
        val v;
    } nd[maxn << 2];
    int cnt;

    int bt(int l, int r) {
        int u = ++cnt;
        nd[u].l = l; nd[u].r = r;
        if (l == r) {
            nd[u].lc = nd[u].rc = -1;
            nd[u].v = a[l];
        } else {
            int mid = (l + r) >> 1;
            nd[u].lc = bt(l, mid);
            nd[u].rc = bt(mid + 1, r);
            nd[u].v = nd[nd[u].lc].v & nd[nd[u].rc].v;
        }
        return u;
    }

    void ch(int u, int p, val x) {
        if (nd[u].l == nd[u].r) {
            nd[u].v = x;
            // nd[u].v.print();
        } else {
            int mid = (nd[u].l + nd[u].r) >> 1;
            if (p <= mid) ch(nd[u].lc, p, x);
            else ch(nd[u].rc, p, x);
            nd[u].v = nd[nd[u].lc].v & nd[nd[u].rc].v;
            // writeln(u, p);
            // nd[u].v.print();
        }
    }

    val query(int u, int l, int r) {
        if (nd[u].l == l && nd[u].r == r) {
            return nd[u].v;
        } else {
            int mid = (nd[u].l + nd[u].r) >> 1;
            if (r <= mid) return query(nd[u].lc, l, r);
            else if (l > mid) return query(nd[u].rc, l, r);
            else {
                val a = query(nd[u].lc, l, mid), b = query(nd[u].rc, mid + 1, r);
                // writeln(l, r);
                // a.print(); b.print();
                return a & b;
            }
        }
    }
} tr;

void get(val &v) {
    v.cnt = 0;
    for (int j = 0; j < n; j++) {
        v.s[0][j] = v.s[1][j] = 0;
        switch (ch[j]) {
            case '0': v.s[0][j] = 0; break;
            case '1': v.s[0][j] = 1; break;
            case '?': v.s[1][j] = 1; v.cnt++; break;
        }
    }
}

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    int ans = 0;

    read(n, m, q);
    for (int i = 1; i <= m; i++) {
        scanf("%s", ch);
        get(a[i]);
    }

    tr.bt(1, m);
    while (q--) {
        int op, x, y;
        read(op, x);
        if (op == 0) {
            read(y);
            int res = tr.query(1, x, y).cnt;
            if (~res) {
                ans ^= (1 << res);
                // writeln(1 << res);
            }
        } else {
            scanf("%s", ch);
            get(a[0]);
            tr.ch(1, x, a[0]);
        }
    }
    writeln(ans);
    return 0;
}