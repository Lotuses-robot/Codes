#include <cstdio>
#include <cstring>
#include <vector>

#define gc getchar()
template<typename T>
void read(T &r) {
    r = 0; static char ch, last;
    ch = gc, last = 'z';
    while (ch < '0' || ch > '9') last = ch, ch = gc;
    while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
    r = (last == '-') ? -r : r;
}

#define mp std::make_pair

const int maxn = 114514;

int a[maxn];

struct segtree {
    struct val {
        int line, lst;
    };

    struct treeNode {
        int l, r, lc, rc;
        int c[25], d[25];
        // c 是 前面多出 i 个空时后面的行数
        // d 是 前面多出 i 个空时后面的空数
    } tr[maxn << 2];
    int cnt;
    struct nodeAns {
        int c[25], d[25];
    };

    void init() {
        cnt = 0;
    }

    int bt(int l, int r) {
        int id = ++cnt;
        treeNode &tn = tr[id];
        tn.l = l; tn.r = r;

        memset(tn.c, 0, sizeof(tn.c));
        memset(tn.d, 0, sizeof(tn.d));
        if (l == r) {
            tn.lc = tn.rc = -1;
            for (int i = 0; i < a[l]; i++) tn.c[i] = 2, tn.d[i] = 24 - a[l];
            for (int i = a[l]; i <= 24; i++) tn.c[i] = 1, tn.d[i] = i - a[l];
        } else {
            int mid = (l + r) >> 1;
            tn.lc = bt(l, mid);
            tn.rc = bt(mid + 1, r);
            for (int i = 0; i <= 24; i++) { // 当左边的前面留下 i 个空的时候
                int hi = tr[tn.lc].d[i]; // 左边能留下多少个空
                tn.c[i] = tr[tn.lc].c[i] + tr[tn.rc].c[hi] - 1;
                        //    左边行数        右边留空后行数
                tn.d[i] = tr[tn.rc].d[hi];
                //     右边留空后最右边剩余的空数
            }
        }
        return id;
    }

    void change(int id, int x, int c) {
        treeNode &tn = tr[id];
        if (tn.l == tn.r) {
            for (int i = 0; i < a[x]; i++) tn.c[i] = 2, tn.d[i] = 24 - a[x];
            for (int i = a[x]; i <= 24; i++) tn.c[i] = 1, tn.d[i] = i - a[x];
        } else {
            int mid = (tn.l + tn.r) >> 1;
            if (x <= mid) change(tn.lc, x, c);
            else if (x > mid) change(tn.rc, x, c);

            for (int i = 0; i <= 24; i++) { // 完全复制 bt
                int hi = tr[tn.lc].d[i];
                tn.c[i] = tr[tn.lc].c[i] + tr[tn.rc].c[hi] - 1;
                tn.d[i] = tr[tn.rc].d[hi];
            }
        }
    }

    void query(int id, int l, int r, nodeAns &g) {
        treeNode &tn = tr[id];
        if (tn.l == l && tn.r == r) {
            memcpy(g.c, tn.c, sizeof(g.c));
            memcpy(g.d, tn.d, sizeof(g.d));
        } else {
            int mid = (tn.l + tn.r) >> 1;
            if (r <= mid) {
                query(tn.lc, l, r, g);
            } else if (l     >= mid + 1) {
                query(tn.rc, l, r, g);
            } else {
                nodeAns lans, rans;
                query(tn.lc, l, mid, lans);
                query(tn.rc, mid + 1, r, rans);

                for (int i = 0; i <= 24; i++) { // 完全复制 bt
                    int hi = lans.d[i];
                    g.c[i] = lans.c[i] + rans.c[hi] - 1;
                    g.d[i] = rans.d[hi];
                }
            }
        }
    }
} seg;

int main() {
    freopen("Editor.in", "r", stdin);
    freopen("Editor.out", "w", stdout);
    int n, m;
    read(n), read(m);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    seg.bt(1, n);
    
    while (m--) {
        int ch, c1, c2;
        read(ch), read(c1), read(c2);
        if (ch == 1) {
            a[c1] = c2;
            seg.change(1, c1, c2);
        } else {
            segtree::nodeAns ans;
            seg.query(1, c1, c2, ans);
            printf("%d\n", ans.c[0] - 1);
        }
    }
    return 0;
}