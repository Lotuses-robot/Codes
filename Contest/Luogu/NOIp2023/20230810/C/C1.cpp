// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <ctime>

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

const int maxn = 2e5 + 5;
struct Tree {
    struct Node {
        int l, r, lc, rc;
        int cnt;
    } nd[maxn << 6];
    int cnt;

    void init() {
        cnt = 0;
    }

    int crNode(int l, int r) {
        int id = ++cnt;
        nd[id].l = l; nd[id].r = r;
        nd[id].cnt = 0;
        nd[id].lc = nd[id].rc = -1;
        return id;
    }

    void upd(int a, int b, int c) {
        // return {a.l, b.r, lc, rc, a.cnt + b.cnt, a.sum + b.sum};
        nd[a].cnt = nd[b].cnt + nd[c].cnt;
    }

    void add(int u, int p, int c) {
        // writeln(u, nd[u].l, nd[u].r);
        if (nd[u].l == p && nd[u].r == p) {
            nd[u].cnt += c;
        } else {
            int mid = (nd[u].l + nd[u].r) >> 1;
            if (p <= mid) {
                if (nd[u].lc == -1) nd[u].lc = crNode(nd[u].l, mid);
                add(nd[u].lc, p, c);
            } else {
                if (nd[u].rc == -1) nd[u].rc = crNode(mid + 1, nd[u].r);
                add(nd[u].rc, p, c);
            }
            // upd(u, nd[u].lc, nd[u].rc);
            nd[u].cnt = 0;
            if (nd[u].lc != -1) nd[u].cnt += nd[nd[u].lc].cnt;
            if (nd[u].rc != -1) nd[u].cnt += nd[nd[u].rc].cnt;
            // nd[u].cnt = nd[nd[u].lc].cnt + nd[nd[u].rc].cnt;
        }
    }

    int query(int u, int l, int r) {
        if (u == -1) return 0;
        if (nd[u].l == l && nd[u].r == r) {
            return nd[u].cnt;
        }
        int mid = (nd[u].l + nd[u].r) >> 1;
        if (r <= mid) return query(nd[u].lc, l, r);
        else if (l > mid) return query(nd[u].rc, l, r);
        else {
            // writeln(query(nd[u].lc, l, mid), query(nd[u].rc, mid + 1, r));
            return query(nd[u].lc, l, mid) + query(nd[u].rc, mid + 1, r);
        }
    }
} tr, ctr;

int rt1, rt2;
int up = 3e14;
int n, k, m, c, d;
int a[maxn];
int del = 0;

void init() {
    ctr.init();
    tr.init();
    rt1 = tr.crNode(0, up);
    rt2 = ctr.crNode(0, up);
    for (int i = m + 1; i <= n; i++) {
        ctr.add(rt2, a[i], 1);
    }
    for (int i = 1; i <= m; i++) {
        tr.add(rt1, a[i] + c + d * (i - 1), 1);
    }
}

bool check(int q) {
    return tr.query(rt1, q + del, up) + ctr.query(rt2, q, up) >= k;
}

int ans = 0;
void f() {
    int l = 0, r = up;
    while (l + 1 < r) {
        int mid = ((r - l) >> 1) + l;
        // if (rand() % 3 == 0) {
        //     mid = 1ll * rand() * rand() * rand() % (r - l >> 1) / 4 * (rand() % 4 + 1) + l;
        // }
        if (check(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    if (check(r)) ans = std::max(ans, r);
    else if (check(l + 1)) ans = std::max(ans, l + 1);
    else ans = std::max(ans, l);
}

int bg;
void find() {
    init();
    f();
    del = 0;
    for (int i = 1; i <= n - m; i++) {
        tr.add(rt1, a[i] + c + d * (i - 1), -1);
        tr.add(rt1, a[i + m] + c + d * (i + m - 1), 1);
        ctr.add(rt2, a[i], 1);
        ctr.add(rt2, a[i + m], -1);
        del += d;
        f();
        if (i % 1000 == 0) {
            if (clock() - bg >= CLOCKS_PER_SEC / 10 * 9.99) {
                return;
            }
        }
    }
}

signed main() {
    #ifdef LOCAL
        freopen("data/array6.in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    bg = clock();

    int max = 0;
    read(n, k, m, c, d);
    for (int i = 1; i <= n; i++) read(a[i]), max = std::max(max, a[i]);

    if (k == 1) {
        int ans = 0;
        for (int i = 1; i <= m; i++) {
            ans = std::max(ans, a[i] + c + d * (i - 1));
        }
        for (int i = m + 1; i <= n; i++) {
            ans = std::max(ans, a[i] + c + d * (m - 1));
        }
        writeln(ans);
        return 0;
    }

    up = max + c + d * n;
    find();
    writeln(ans);

    return 0;
}