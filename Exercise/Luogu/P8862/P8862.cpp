// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>

#define int long long
#define gc getchar()
template<typename T>
void read(T &r) { // NOLINT
    r = 0; static char ch, last; // NOLINT
    ch = gc, last = 'z';
    while (ch < '0' || ch > '9') last = ch, ch = gc;
    while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
    r = (last == '-') ? -r : r;
}

template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) { // NOLINT
    read(arg);
    read(arg_left...);
}

namespace data {
    const int maxN = 800005;
}

struct SegTree {
    struct Node {
        int l, r, lc, rc;
        int lazy, ans;
    } nd[data::maxN];
    int a[data::maxN];

    int len;
    void init() {
        len = 0;
    }

    void update(int pt) {
        if (pt == -1) return;
        int lz = nd[pt].lazy; nd[pt].lazy = 0;
        if (nd[pt].lc != -1) nd[nd[pt].lc].ans += lz, nd[nd[pt].lc].lazy += lz;
        if (nd[pt].rc != -1) nd[nd[pt].rc].ans += lz, nd[nd[pt].rc].lazy += lz;
    }

    int build(int l, int r) {
        int id = ++len;
        nd[id].l = l; nd[id].r = r;
        nd[id].lazy = 0;
        if (l == r) {
            nd[id].lc = nd[id].rc = -1;
            nd[id].ans = a[l];
        } else {
            int mid = (l + r) >> 1;
            nd[id].lc = build(l, mid);
            nd[id].rc = build(mid + 1, r);
            nd[id].ans = std::min(nd[nd[id].lc].ans, nd[nd[id].rc].ans);
        }
        return id;
    }

    void change(int pt, int l, int r, int x) {
        update(pt);
        if (nd[pt].l == l && nd[pt].r == r) {
            nd[pt].ans += x;
            nd[pt].lazy += x;
        } else {
            int mid = (nd[pt].l + nd[pt].r) >> 1;
            if (r <= mid) change(nd[pt].lc, l, r, x);
            else if (l > mid) change(nd[pt].rc, l, r, x);
            else {
                change(nd[pt].lc, l, mid, x);
                change(nd[pt].rc, mid + 1, r, x);
            }
            nd[pt].ans = std::min(nd[nd[pt].lc].ans, nd[nd[pt].rc].ans);
        }
    }

    int query(int pt, int l, int r) {
        // printf("%d\n", pt);
        update(pt);
        if (nd[pt].l == l && nd[pt].r == r) {
            return nd[pt].ans;
        } else {
            int mid = (nd[pt].l + nd[pt].r) >> 1;
            if (r <= mid) return query(nd[pt].lc, l, r);
            else if (l > mid) return query(nd[pt].rc, l, r);
            else return std::min(query(nd[pt].lc, l, mid), query(nd[pt].rc, mid + 1, r));
        }
    }
} tr;

int org[data::maxN];
int op[data::maxN];
int left[data::maxN], right[data::maxN];
int num[data::maxN];

signed main() {
    #ifdef LOCAL
        freopen("restore/restore2.in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    int T;
    read(T);
    while (T--) {
        int n, q;
        read(n, q);
        for (int i = 0; i < n; i++) {
            read(org[i]);
        }
        for (int i = 0; i < q; i++) {
            read(op[i]);
            if (op[i] == 1) {
                read(left[i], right[i], num[i]);
            } else {
                read(left[i], right[i]);
            }
        }
        for (int i = 1; i <= n; i++) {
            read(tr.a[i]);
        }
        tr.init();
        tr.build(1, n);

        for (int i = q - 1; i >= 0; i--) {
            if (op[i] == 1) {
                tr.change(1, left[i], right[i], -num[i]);
            } else {
                num[i] = tr.query(1, left[i], right[i]);
            }
        }

        for (int i = 0; i < q; i++) {
            if (op[i] == 2) {
                printf("%lld ", num[i]);
            }
        }
        puts("");
    }
    return 0;
}
