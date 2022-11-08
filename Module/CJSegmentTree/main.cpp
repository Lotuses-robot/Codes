#include <cstdio>
#include <cstring>

char ch, last;
#define gc getchar()
template<typename T>
void read(T &r) {
    r = 0;
    ch = gc, last = 'z';
    while (ch < '0' || ch > '9') last = ch, ch = gc;
    while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
    if (last == '-') r = -r;
}

#define maxn 100005
#define max(a, b) ((a) > (b) ? (a) : (b))
template <typename T> struct segmt {
    struct TreeNode {
        int l, r, lc, rc;
        T ans, lazy;
        TreeNode() { l = r = lc = rc = ans = lazy = 0; }
    } tn[14 * maxn];
    T a[maxn * 2];
    int tot, n;
    int hrt[maxn * 2];
    int tot2;

    void init() {
        tot = tot2 = 0;
    }

    int New() {
        tn[++tot] = TreeNode();
        return tot;
    }

    int NewHist() {
        hrt[++tot2] = 0;
        return tot2;
    }

    int NowHist() {
        return tot2;
    }

    void BackHist(int x) {
        tot2 = x;
    }

    inline int bt(int l, int r) {
        int pos = ++tot;
        tn[pos].l = l;
        tn[pos].r = r;
        tn[pos].lazy = 0;
        if (l == r) {
            tn[pos].lc = tn[pos].rc = -1;
            tn[pos].ans = a[l];
        } else {
            tn[pos].lc = bt(l, (l + r) >> 1);
            tn[pos].rc = bt(((l + r) >> 1) + 1, r);
            tn[pos].ans = (tn[tn[pos].lc].ans + tn[tn[pos].rc].ans);
        }
        return pos;
    }
    void change(int orp, int &p, int l, int r, T x) {
        p = New();
        tn[p] = tn[orp];
        if (tn[p].l == l && tn[p].r == r) {
            tn[p].lazy += x;
            tn[p].ans += x * (r - l + 1);
            return;
        }
        if (r <= tn[tn[p].lc].r) {
            change(tn[orp].lc, tn[p].lc, l, r, x);
        } else if (tn[tn[p].rc].l <= l) {
            change(tn[orp].rc, tn[p].rc, l, r, x);
        } else {
            change(tn[orp].lc, tn[p].lc, l, tn[tn[orp].lc].r, x);
            change(tn[orp].rc, tn[p].rc, tn[tn[orp].rc].l, r, x);
        }
        tn[p].ans = tn[tn[p].lc].ans + tn[tn[p].rc].ans;
    }
    int query(int p, int l, int r) {
        if (tn[p].l == l && tn[p].r == r) {
            return tn[p].ans + tn[p].lazy * (tn[p].r - tn[p].l + 1);
        }
        if (r <= tn[tn[p].lc].r) {
            return query(tn[p].lc, l, r);
        } else if (tn[tn[p].rc].l <= l) {
            return query(tn[p].rc, l, r);
        } else {
            return query(tn[p].lc, l, tn[tn[p].lc].r)
                +  query(tn[p].rc, tn[tn[p].rc].l, r);
        }
    }   
};
segmt<int> sg;

int main() {
    static char ch[114];
    int n, m;
    int l, r, d, t;
    while (scanf("%d%d", &n, &m) != EOF) {
        sg.init();
        for (int i = 1; i <= n; i++) {
            read(sg.a[i]);
        }
        sg.bt(1, n);
        sg.hrt[sg.NewHist()] = 1;
        
        for (int i = 0; i < m; i++) {
            scanf("%s", ch);
            if (ch[0] == 'C') {
                read(l); read(r); read(d);
                int passed = sg.hrt[sg.NowHist()];
                sg.change(passed, sg.hrt[sg.NewHist()], l, r, d);
            } if (ch[0] == 'Q') {
                read(l); read(r);
                printf("%d\n", sg.query(sg.hrt[sg.NowHist()], l, r));
            } if (ch[0] == 'H') {
                read(l); read(r); read(t);
                printf("%d\n", sg.query(sg.hrt[t + 1], l, r));
            } if (ch[0] == 'B') {
                read(t);
                sg.BackHist(t);
            }
        }
    }
    return 0;
}