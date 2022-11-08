#include <cstdio>
#include <utility>

#define maxn 100001

template<typename T>
struct LeftTree {
    struct TreeNode {
        int id, l, r, rt, dist;
        T val;
        bool del;
        bool operator < (TreeNode b) const {
            if (val != b.val) return val < b.val;
            return id < b.id;
        }
    };

    TreeNode nd[maxn];
    T a[maxn];

    #define lc(x) nd[x].l
    #define rc(x) nd[x].r

    void init(int n) {
        for (int i = 1; i <= n; i++) {
            nd[i].id = i;
            nd[i].val = a[i];
            nd[i].rt = i;
            nd[i].l = nd[i].r = 0;
            nd[i].dist = 0;
            nd[i].del = false;
        }
        nd[0].dist = -1;
    }

    int merge(int x, int y) {
        // if (find(x) == find(y) && find(x) != 0 || x == y) return nd[x].rt;
        if (!x || !y) return x + y;
        if (nd[x] < nd[y]) std::swap(x, y);
        rc(x) = merge(rc(x), y);
        if (nd[lc(x)].dist < nd[rc(x)].dist) std::swap(lc(x), rc(x));
        nd[x].dist = nd[rc(x)].dist + 1;
        nd[lc(x)].rt = nd[x].rt;
        if (rc(x) != 0) nd[rc(x)].rt = nd[x].rt;
        return x;
    }

    int find(int x) {
        return nd[x].rt == x ? x : nd[x].rt = find(nd[x].rt);
    }
};
LeftTree<int> tr;

int main() {
    int n, lrt, rrt, nrt;
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; i++) {
            scanf("%d", &tr.a[i]);
        }
        tr.init(n);
        int m;
        scanf("%d", &m);
        while (m--) {
            int x, y;
            scanf("%d%d", &x, &y);
            x = tr.find(x);
            y = tr.find(y);

            if (x == y) {
                puts("-1");
                continue;
            }

            lrt = tr.nd[tr.lc(x)].rt = tr.nd[tr.rc(x)].rt = tr.nd[x].rt = tr.merge(tr.lc(x), tr.rc(x));
            tr.lc(x) = tr.rc(x) = tr.nd[x].dist = 0;

            rrt = tr.nd[tr.lc(y)].rt = tr.nd[tr.rc(y)].rt = tr.nd[y].rt = tr.merge(tr.lc(y), tr.rc(y));
            tr.lc(y) = tr.rc(y) = tr.nd[y].dist = 0;

            tr.nd[x].val /= 2;
            tr.nd[y].val /= 2;

            if (tr.nd[x].rt == 0) tr.nd[x].rt = x;
            if (tr.nd[y].rt == 0) tr.nd[y].rt = y;

            nrt;
            // lrt = tr.merge(lrt, rrt);
            if (!lrt && !rrt) {
                nrt = x;
            } else if (!lrt) {
                nrt = rrt;
            } else if (!rrt) {
                nrt = lrt;
            } else {
                nrt = tr.merge(lrt, rrt);
            }
            if (lrt + rrt != 0) nrt = tr.merge(nrt, x);
            nrt = tr.merge(nrt, y);
            printf("%d\n", tr.nd[nrt].val);
        }
    }
    return 0;
}