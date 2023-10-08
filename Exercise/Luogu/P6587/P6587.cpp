// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <assert.h>
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

const int maxn = 2e6 + 10;
int n, m;
int a[maxn];
bool check(int b, int p, int cnt) {
    if (p == 0) p = b;
    int ct = 0;
    while (p <= n) ct++, p += b;
    return cnt == ct;
}

struct Tree {
    struct Node {
        int b, p, lc, rc, cnt, sum, lazy;
    } nd[maxn];
    int cnt;

    void pushd(int u) {
        if (!nd[u].lazy) return;
        int lc = nd[u].lc, rc = nd[u].rc;
        if (~lc) {
            nd[lc].sum += nd[lc].cnt * nd[u].lazy;
            nd[lc].lazy += nd[u].lazy;
        }
        if (~rc) {
            nd[rc].sum += nd[rc].cnt * nd[u].lazy;
            nd[rc].lazy += nd[u].lazy;
        }
        nd[u].lazy = 0;
    }

    void upd(int u) {
        int lc = nd[u].lc, rc = nd[u].rc;
        nd[u].sum = 0;
        if (~lc) nd[u].sum += nd[lc].sum;
        if (~rc) nd[u].sum += nd[rc].sum;
    }

    int bt(int b, int p) {
        int u = ++cnt;
        nd[u].b = b; nd[u].p = p;
        if (p == 0) p = b;
        if (n >= p) nd[u].cnt = (n - p) / b + 1;
        if (nd[u].cnt < 1) { nd[u].cnt = 0; return u; }
        if (nd[u].cnt == 1) {
            nd[u].sum = a[p];
            nd[u].lc = nd[u].rc = -1;
        } else {
            if (p == b) p = 0;
            nd[u].lc = bt(b << 1, p);
            nd[u].rc = bt(b << 1, p + b);
            upd(u);
        }
        assert(check(nd[u].b, nd[u].p, nd[u].cnt));
        // writeln(n, nd[u].b, nd[u].p, nd[u].cnt);
        // writeln(u, nd[u].lc, nd[u].rc, nd[u].b, nd[u].p, nd[u].cnt);
        return u;
    }

    void add(int u, int b, int p, int x) {
        // writeln(u, nd[u].b, nd[u].p, nd[u].cnt);
        if (!(~u)) return;
        if (nd[u].b == b) {
            nd[u].sum += x * nd[u].cnt;
            nd[u].lazy += x;
        } else {
            pushd(u);
            if (p & 1) add(nd[u].rc, b, p >> 1, x);
            else add(nd[u].lc, b, p >> 1, x);
            upd(u);
        }
    }

    int query(int u, int b, int p) {
        // writeln(u, nd[u].b, nd[u].p, nd[u].cnt);
        if (!(~u)) return 0;
        if (nd[u].b == b) {
            return nd[u].sum;
        } else {
            pushd(u);
            if (p & 1) return query(nd[u].rc, b, p >> 1);
            else return query(nd[u].lc, b, p >> 1);
        }
    }
} tr;

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    int lastans = 0;
    read(n, m);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    tr.bt(1, 0);
    while (m--) {
        int op, x, y, z;
        read(op, x, y);
        // int rs = scanf("%lld%lld%lld", &op, &x, &y);
        // if (rs < 3) return 0;
        // op = (lastans + op) % 2 + 1;
        if (op == 1) {
            // rs = scanf("%lld", &z);
            // if (rs < 1) return 0;
            read(z);
            tr.add(1, 1 << x, y, z);
        } else {
            lastans = tr.query(1, 1 << x, y);
            writeln(lastans);
        }
    }
    return 0;
}