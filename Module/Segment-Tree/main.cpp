// usage see BZOJ1036

#include <cstdio>
#include <cstring>

#define maxn 1000006
#define max(a, b) ((a) > (b) ? (a) : (b))
template <typename T> struct segmt {
    struct tree {
        int l, r, lc, rc;
        T ans, lazy2;
        T ansMax;
    } tr[2 * maxn];
    T a[maxn];
    int tot, n;
    inline int bt(int l, int r) {
        int pos = ++tot;
        tr[pos].l = l;
        tr[pos].r = r;
        tr[pos].lazy2 = 0;
        if (l == r) {
            tr[pos].lc = tr[pos].rc = -1;
            tr[pos].ans = a[l];
            tr[pos].ansMax = a[l];
        } else {
            tr[pos].lc = bt(l, l + r >> 1);
            tr[pos].rc = bt((l + r >> 1) + 1, r);
            tr[pos].ans = (tr[tr[pos].lc].ans + tr[tr[pos].rc].ans);
            tr[pos].ansMax = max(tr[tr[pos].lc].ansMax, tr[tr[pos].rc].ansMax);
        }
        return pos;
    }
    inline void update(int pos) {
        if (tr[pos].lazy2) {
            change(tr[pos].lc, tr[tr[pos].lc].l, tr[tr[pos].lc].r, tr[pos].lazy2);
            change(tr[pos].rc, tr[tr[pos].rc].l, tr[tr[pos].rc].r, tr[pos].lazy2);
            tr[pos].lazy2 = 0;
        }
        tr[pos].ans = (tr[tr[pos].lc].ans + tr[tr[pos].rc].ans);
        tr[pos].ansMax = max(tr[tr[pos].lc].ansMax, tr[tr[pos].rc].ansMax);
    }
    inline void change(int pos, int l, int r, T x) {
        if (tr[pos].l == l && tr[pos].r == r) {
            tr[pos].lazy2 = (tr[pos].lazy2 + x);
            tr[pos].ans = x * (r - l + 1);
            tr[pos].ansMax = x;
            return;
        }
        update(pos);
        if (r <= tr[tr[pos].lc].r)
            change(tr[pos].lc, l, r, x);
        else if (l >= tr[tr[pos].rc].l)
            change(tr[pos].rc, l, r, x);
        else {
            change(tr[pos].lc, l, tr[tr[pos].lc].r, x);
            change(tr[pos].rc, tr[tr[pos].rc].l, r, x);
        }
        tr[pos].ans = (tr[tr[pos].lc].ans + tr[tr[pos].rc].ans);
        tr[pos].ansMax = max(tr[tr[pos].lc].ansMax, tr[tr[pos].rc].ansMax);
    }
    inline int query1(int pos, int l, int r) {
        if (tr[pos].l == l && r == tr[pos].r)
            return tr[pos].ans;
        update(pos);
        if (r <= tr[tr[pos].lc].r)
            return query1(tr[pos].lc, l, r);
        else if (l >= tr[tr[pos].rc].l)
            return query1(tr[pos].rc, l, r);
        else
            return query1(tr[pos].lc, l, tr[tr[pos].lc].r) +
                            query1(tr[pos].rc, tr[tr[pos].rc].l, r);
    }
    inline int query2(int pos, int l, int r) {
        if (tr[pos].l == l && r == tr[pos].r)
            return tr[pos].ansMax;
        update(pos);
        if (r <= tr[tr[pos].lc].r)
            return query2(tr[pos].lc, l, r);
        else if (l >= tr[tr[pos].rc].l)
            return query2(tr[pos].rc, l, r);
        else
            return max(query2(tr[pos].lc, l, tr[tr[pos].lc].r), 
                            query2(tr[pos].rc, tr[tr[pos].rc].l, r));
    }
};
segmt<int> sg;

int main() {
    while (true) {
        scanf("%d", &sg.n);
        for (int i = 1; i <= sg.n; i++) {
            scanf("%d", &sg.a[i]);
        }
        sg.bt(1, sg.n);
        while (true) {
            int op, x, y;
            scanf("%d%d%d", &op, &x, &y);
            if (op == 1) {
                sg.change(1, x, x, y);
            } else if (op == 2) {
                printf("%d\n", sg.query1(1, x, y));
            } else if (op == 3) {
                printf("%d\n", sg.query2(1, x, y));
            }
        }
    }
    return 0;
}