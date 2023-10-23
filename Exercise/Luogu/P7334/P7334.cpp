// Copyright 2023 Lotuses
#define tsz signed
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
// #include <map>
// #include <set>
// #include <queue>
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
#define ins(a, b) (G[a].push_back(b))

#define int long long

const double eps = 1e-8;
const int maxn = 2e5 + 10, mod = 998244353;
int n, m, a[maxn], ct[maxn];

int qpow(int x, int ct) {
    int ans = 1;
    do {
        if (ct & 1) ans = ans * x % mod;
        x *= x; x %= mod;
    } while (ct >>= 1);
    return ans;
}

void gsqt(int &x, int &cnt) {
    cnt = 0;
    if (x == 1) return;
    int sqt = sqrt(x) + eps;
    while (sqt * sqt == x) {
        x = sqt; cnt++;
        sqt = sqrt(x) + eps;
    }
}

int pow2[1000010];

struct Segt {
    struct Node {
        int l, r, lc, rc;
        int val, cnt, lazy;
    } nd[maxn << 3];
    int cnt;

    Segt() { cnt = 0; }
    int bt(int l, int r) {
        int u = ++cnt;
        nd[u].l = l; nd[u].r = r;
        if (l == r) {
            nd[u].cnt = ct[l]; nd[u].val = a[l];
            nd[u].lazy = 0;
            nd[u].lc = nd[u].rc = -1;
        } else {
            int mid = (l + r) >> 1;
            nd[u].lc = bt(l, mid);
            nd[u].rc = bt(mid + 1, r);
            nd[u].cnt = std::min(nd[nd[u].lc].cnt, nd[nd[u].rc].cnt);
            nd[u].val = std::max(nd[nd[u].lc].val, nd[nd[u].rc].val);
        }
        return u;
    }

    void pushd(int u) {
        if (nd[u].lazy) {
            int lc = nd[u].lc, rc = nd[u].rc;
            if (~lc) {
                nd[lc].cnt += nd[u].lazy;
                nd[lc].lazy += nd[u].lazy;
            }
            if (~rc) {
                nd[rc].cnt += nd[u].lazy;
                nd[rc].lazy += nd[u].lazy;
            }
            nd[u].lazy = 0;
        }
    }

    void add(int u, int l, int r) {
        if (nd[u].l == l && nd[u].r == r) {
            nd[u].lazy++;
            nd[u].cnt++;
        } else {
            pushd(u);
            int mid = (nd[u].l + nd[u].r) >> 1;
            if (r <= mid) add(nd[u].lc, l, r);
            else if (l > mid) add(nd[u].rc, l, r);
            else add(nd[u].lc, l, mid), add(nd[u].rc, mid + 1, r);
            nd[u].cnt = std::min(nd[nd[u].lc].cnt, nd[nd[u].rc].cnt);
        }
    }

    void sqt(int u, int l, int r) {
        if (nd[u].val <= 1) return;
        if (nd[u].l == nd[u].r) {
            if (nd[u].cnt <= 0) {
                nd[u].val = sqrt(nd[u].val) + eps;
                gsqt(nd[u].val, nd[u].cnt);
            } else {
                nd[u].cnt--;
            }
        } else if (nd[u].l == l && nd[u].r == r) {
            if (nd[u].cnt <= 0) {
                pushd(u); int mid = (l + r) >> 1;
                nd[u].cnt = 1e18;
                nd[u].val = -1e18;
                if (~nd[u].lc) {
                    sqt(nd[u].lc, l, mid);
                    nd[u].cnt = std::min(nd[nd[u].lc].cnt, nd[u].cnt);
                    nd[u].val = std::max(nd[nd[u].lc].val, nd[u].val);
                }
                if (~nd[u].rc) {
                    sqt(nd[u].rc, mid + 1, r);
                    nd[u].cnt = std::min(nd[nd[u].rc].cnt, nd[u].cnt);
                    nd[u].val = std::max(nd[nd[u].rc].val, nd[u].val);
                }
            } else {
                nd[u].cnt--;
                nd[u].lazy--;
            }
        } else {
            int mid = nd[u].l + nd[u].r >> 1;
            pushd(u);
            if (r <= mid) sqt(nd[u].lc, l, r);
            else if (l > mid) sqt(nd[u].rc, l, r);
            else {
                sqt(nd[u].lc, l, mid);
                sqt(nd[u].rc, mid + 1, r);
            }
            nd[u].cnt = std::min(nd[nd[u].lc].cnt, nd[nd[u].rc].cnt);
            nd[u].val = std::max(nd[nd[u].lc].val, nd[nd[u].rc].val);
        }
    }

    int sum(int u) {
        if (nd[u].l == nd[u].r) {
            // writeln(nd[u].l, nd[u].val, nd[u].cnt);
            return qpow(nd[u].val, pow2[nd[u].cnt]);
        }
        if (nd[u].val <= 1) {
            return nd[u].r - nd[u].l + 1;
        } else {
            pushd(u);
            return (sum(nd[u].lc) + sum(nd[u].rc)) % mod;
        }
    }
} tr;

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    read(n, m);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
        gsqt(a[i], ct[i]);
        // writeln(a[i], ct[i]);
    }
    pow2[0] = 1;
    for (int i = 1; i <= 1e6; i++) {
        pow2[i] = pow2[i - 1] << 1;
        pow2[i] %= (mod - 1);
    }
    tr.bt(1, n);
    // puts("?");
    for (int i = 1; i <= m; i++) {
        int op, l, r;
        read(op, l, r);
        if (op == 1) {
            tr.sqt(1, l, r);
        } else {
            tr.add(1, l, r);
        }
    }
    // puts("?");
    writeln(tr.sum(1));
    return 0;
}