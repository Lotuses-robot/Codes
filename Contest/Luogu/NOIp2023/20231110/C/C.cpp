// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <vector>
// #include <map>
// #include <set>
// #include <list>
// #include <queue>
// #include <stack>
// #include <string>
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
#define ins(a, b) (G[a].emplace_back(b))

const int maxn = 1e5 + 10;
int a[maxn];

void max(int a, int alen, int b, int blen, int &c, int &clen) {
    if (a > b) {
        c = a;
        clen = alen;
    } else if (a < b) {
        c = b;
        clen = blen;
    } else {
        c = a;
        clen = std::min(alen, blen);
    }
}

struct Tree {
    struct Node {
        int l, r, lc, rc;
        struct Value {
            int lmax[2][2], llen[2][2], rmax[2][2], rlen[2][2], sum[2];
            int maxx[2], maxlen[2];
            int lazy, len;

            void init(int len) {
                this -> len = len;
                memset(lmax, -63, sizeof(lmax));
                memset(rmax, -63, sizeof(rmax));
                memset(llen, 0, sizeof(llen));
                memset(rlen, 0, sizeof(rlen));
                memset(sum, 0, sizeof(sum));
                memset(maxx, -63, sizeof(maxx));
                memset(maxlen, 0, sizeof(maxlen));
            }

            Value operator * (const Value b) const {
                const Value &a = *this; static Value c; static bool l, r;
                l = a.len & 1, r = b.len & 1;
                for (int i = 0; i < 2; i++) {
                    for (int j = 0; j < 2; j++) {
                        max(a.lmax[i][j], a.llen[i][j], a.sum[i] + b.lmax[i ^ l][j ^ l], a.len + b.llen[i ^ l][j ^ l], c.lmax[i][j], c.llen[i][j]);
                    }
                }
                for (int i = 0; i < 2; i++) {
                    for (int j = 0; j < 2; j++) {
                        max(a.rmax[i][j], a.rlen[i][j], b.sum[(!i) ^ r] + a.rmax[!i][j ^ r], b.len + a.rlen[!i][j ^ r], c.rmax[i][j], c.rlen[i][j]);
                    }
                }
                for (int i = 0; i < 2; i++) {
                    c.sum[i] = a.sum[i] + b.sum[l ^ i];
                    max(a.maxx[i], a.maxlen[i], b.maxx[i], b.maxlen[i], c.maxx[i], c.maxlen[i]);
                                            // last--v  v--len
                    max(c.maxx[i], c.maxlen[i], a.rmax[1][0] + b.lmax[0][i], a.rlen[1][0] + b.llen[0][i], c.maxx[i], c.maxlen[i]);
                    max(c.maxx[i], c.maxlen[i], a.rmax[0][1] + b.lmax[1][i ^ 1], a.rlen[0][1] + b.llen[1][i ^ 1], c.maxx[i], c.maxlen[i]);
                }
                c.len = a.len + b.len;
                return c;
            }

            Value operator += (int val) {
                lazy += val;
                lmax[0][1] -= val; lmax[1][1] += val;
                rmax[0][1] -= val; rmax[1][1] += val;
                if (len & 1) sum[0] -= val, sum[1] += val;
                maxx[1] -= val;
                return *this;
            }
        } val;
    } nd[maxn << 2];
    int cnt;
    void init() {
        cnt = 0;
    }

    int bt(int l, int r) {
        int u = ++cnt;
        nd[u].l = l; nd[u].r = r;
        nd[u].lc = nd[u].rc = -1;
        nd[u].val.init(r - l + 1);
        nd[u].val.lazy = 0;
        if (l == r) {
            nd[u].val.lmax[0][1] = -a[l];
            nd[u].val.lmax[1][1] = a[l];
            nd[u].val.llen[0][1] = nd[u].val.llen[1][1] = 1;
            nd[u].val.rmax[0][1] = -a[l];
            nd[u].val.rmax[1][1] = a[l];
            nd[u].val.rlen[0][1] = nd[u].val.rlen[1][1] = 1;
            nd[u].val.sum[0] = -a[l];
            nd[u].val.sum[1] = a[l];
            nd[u].val.maxx[1] = nd[u].val.maxlen[1] = 0;
        } else {
            int mid = (l + r) >> 1;
            nd[u].lc = bt(l, mid);
            nd[u].rc = bt(mid + 1, r);
            nd[u].val = nd[nd[u].lc].val * nd[nd[u].rc].val;
        }
        return u;
    }

    void add(int u, int l, int r, int x) {
        if (nd[u].l == l && nd[u].r == r) {
            nd[u].val += x;
        } else {
            if (nd[u].val.lazy) {
                nd[nd[u].lc].val += nd[u].val.lazy;
                nd[nd[u].rc].val += nd[u].val.lazy;
            }
            int mid = (nd[u].l + nd[u].r) >> 1;
            if (r <= mid) add(nd[u].lc, l, r, x);
            else if (l > mid) add(nd[u].rc, l, r, x);
            else add(nd[u].lc, l, mid, x), add(nd[u].rc, mid + 1, r, x);
        }
    }
} tr;

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    int T;
    read(T);
    while (T--) {
        tr.init();
        int n, Q;
        read(n, Q);
        for (int i = 1; i <= n; i++) read(a[i]);
        tr.bt(1, n);
        while (Q--) {
            static int op, x, y, z;
            read(op);
            if (op == 0) {
                read(x, y, z);
                tr.add(1, x, y, z);
            } else {
                // writeln(tr.nd[1].val.maxx[], tr.nd[1].val.maxlen);
                int a, b;
                max(tr.nd[1].val.maxx[0], tr.nd[1].val.maxlen[0], tr.nd[1].val.maxx[1], tr.nd[1].val.maxlen[1], a, b);
                writeln(a, b);
            }
        }
    }
    return 0;
}