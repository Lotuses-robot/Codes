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

#define maxn 1000006
#define max(a, b) ((a) > (b) ? (a) : (b))
template <typename T> struct segmt {
    struct tree {
        int l, r, lc, rc;
        T ans;
    } tr[4 * maxn];
    int tot, n;
    inline int bt(int l, int r) {
        int pos = ++tot;
        tr[pos].l = l;
        tr[pos].r = r;
        if (l == r) {
            tr[pos].lc = tr[pos].rc = -1;
            tr[pos].ans = 0;
        } else {
            tr[pos].lc = bt(l, l + r >> 1);
            tr[pos].rc = bt((l + r >> 1) + 1, r);
            tr[pos].ans = 0;
        }
        return pos;
    }
    inline void add(int pos, int pt) {
        if (tr[pos].l == tr[pos].r && tr[pos].l == pt) {
            tr[pos].ans++;
            return;
        }
        if (pt <= tr[tr[pos].lc].r) add(tr[pos].lc, pt);
        else                        add(tr[pos].rc, pt);
        tr[pos].ans = (tr[tr[pos].lc].ans + tr[tr[pos].rc].ans);
    }
    inline int query(int pos, int l, int r) {
        if (tr[pos].l == l && r == tr[pos].r)
            return tr[pos].ans;
        if (r <= tr[tr[pos].lc].r)
            return query(tr[pos].lc, l, r);
        else if (l >= tr[tr[pos].rc].l)
            return query(tr[pos].rc, l, r);
        else
            return query(tr[pos].lc, l, tr[tr[pos].lc].r) +
                            query(tr[pos].rc, tr[tr[pos].rc].l, r);
    }
};

segmt<int> sg;

int a[114514];

signed main() {
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
    sg.bt(1, 200000);
    int n;
    read(n);
    for (int i = 0; i < n; i++) {
        read(a[i]);
    }

    int ans = 0;
    sg.add(1, a[n - 1]);
    for (int i = n - 2; i >= 0; i--) {
        ans += sg.query(1, 1, a[i]);
        sg.add(1, a[i]);
    }
    printf("%lld\n", ans);
    return 0;
}
