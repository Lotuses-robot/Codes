#include <cstdio>
#include <algorithm>
#include <map>

std::map<int, int> Pid;
std::map<int, int> P;

struct Node {
    int s, t, x, l, r;
    bool operator < (Node b) const {
        return x > b.x;
    }
} nd[214514];

int que[214514];

#define maxn 1000006
#define max(a, b) ((a) > (b) ? (a) : (b))
template <typename T> struct segmt {
    struct tree {
        int l, r, lc, rc;
        T ans, lazy2;
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
        } else {
            tr[pos].lc = bt(l, l + r >> 1);
            tr[pos].rc = bt((l + r >> 1) + 1, r);
            tr[pos].ans = (tr[tr[pos].lc].ans + tr[tr[pos].rc].ans);
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
    }
    inline void change(int pos, int l, int r, T x) {
        if (tr[pos].l == l && tr[pos].r == r) {
            tr[pos].lazy2 = (tr[pos].lazy2 + x);
            tr[pos].ans = x * (r - l + 1);
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
    }
    inline int query(int pos, int l, int r) {
        if (tr[pos].l == l && r == tr[pos].r)
            return tr[pos].ans;
        update(pos);
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


int main() {
    freopen("noway.in", "r", stdin);
    freopen("noway.out", "w", stdout);
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d", &nd[i].s, &nd[i].t, &nd[i].x);
        nd[i].l = nd[i].s - nd[i].x;
        nd[i].r = nd[i].t - 1 - nd[i].x;
        Pid[nd[i].l] = 1;
        Pid[nd[i].r] = 1;
    }

    for (int i = 0; i < q; i++) {
        scanf("%d", &que[i]);
        Pid[que[i]] = 1;
    }

    int tot = 0;
    for (std::map<int, int>::iterator i = Pid.begin(); i != Pid.end(); i++) {
        i -> second = ++tot;
        P[tot] = i -> first;
    }
    std::sort(nd, nd + n);

    // build
    sg.bt(1, tot);
    for (int i = 0; i < n; i++) {
        sg.change(1, Pid[nd[i].l], Pid[nd[i].r], i + 1);
    }

    // query offline
    for (int i = 0; i < q; i++) {
        int POS = Pid[que[i]];
        int id = sg.query(1, POS, POS);
        if (id == 0) {
            puts("-1");
        } else {
            printf("%d\n", nd[id - 1].x);
        }
    }
    return 0;
}