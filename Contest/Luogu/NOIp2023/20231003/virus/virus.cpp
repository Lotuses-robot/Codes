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

const int maxn = 1e6 + 10;
int a[maxn];

struct Tree {
    struct Node {
        int l, r, lc, rc;
        int lazy, max;
    } tn[maxn << 3];
    int cnt;
    void init() {
        // memset(tn, 0, sizeof(tn));
        cnt = 0;
    }
    void pushd(int u) {
        if (tn[u].lazy) {
            if (~tn[u].lc) {
                Node &lc = tn[tn[u].lc];
                lc.lazy += tn[u].lazy;
                lc.max += tn[u].lazy;
            }
            if (~tn[u].rc) {
                Node &rc = tn[tn[u].rc];
                rc.lazy += tn[u].lazy;
                rc.max += tn[u].lazy;
            }
        }
        tn[u].lazy = 0;
    }
    void upd(int u) {
        tn[u].max = std::max(tn[tn[u].lc].max, tn[tn[u].rc].max);
    }
    int bt(int l, int r) {
        int u = ++cnt;
        tn[u].l = l; tn[u].r = r;
        tn[u].lazy  = 0;
        if (l == r) {
            tn[u].lc = tn[u].rc = -1;
            tn[u].max = a[l];
        } else {
            int mid = (l + r) >> 1;
            tn[u].lc = bt(l, mid);
            tn[u].rc = bt(mid + 1, r);
            upd(u);
        }
        return u;
    }
    void add(int u, int l, int r, int val) {
        if (tn[u].l == l && tn[u].r == r) {
            tn[u].lazy += val;
            tn[u].max += val;
        } else {
            pushd(u);
            int mid = (tn[u].l + tn[u].r) >> 1;
            if (r <= mid) add(tn[u].lc, l, r, val);
            else if (l > mid) add(tn[u].rc, l, r, val);
            else {
                add(tn[u].lc, l, mid, val);
                add(tn[u].rc, mid + 1, r, val);
            }
            upd(u);
        }
    }
    int query(int u, int l, int r) {
        if (tn[u].l == l && tn[u].r == r) {
            return tn[u].max;
        }
        pushd(u);
        int mid = (tn[u].l + tn[u].r) >> 1;
        if (r <= mid) return query(tn[u].lc, l, r);
        else if (l > mid) return query(tn[u].rc, l, r);
        else return std::max(query(tn[u].lc, l, mid), query(tn[u].rc, mid + 1, r));
    }
} tr;

int l[maxn], r[maxn], w[maxn];

tsz main() {
    // freopen("virus.in", "r", stdin);
    // freopen("virus.out", "w", stdout);
    
    tr.init();
    int n, m;
    read(n, m);

    for (int i = 1; i <= n; i++) {
        read(l[i], r[i], w[i]);
        // tr.add(1, l[i], r[i], w[i]);
        a[l[i]] += w[i];
        a[r[i] + 1] -= w[i];
    }
    for (int i = 2; i <= n; i++) {
        a[i] += a[i - 1];
    }
    tr.bt(1, m);
    // return 0;
    for (int i = 1; i <= n; i++) {
        tr.add(1, l[i], r[i], -w[i]);
        writeln(tr.tn[1].max);  
        tr.add(1, l[i], r[i], w[i]);
    }
    return 0;
}