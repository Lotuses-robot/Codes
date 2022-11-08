#include <cstdio>
#include <utility>

#define maxn 114514

template<typename T>
struct LeftTree {
    struct TreeNode {
        int id, l, r, rt, dist;
        T val;
        bool del;
        bool operator < (TreeNode b) const {
            if (val != b.val) return val > b.val;
            return id > b.id;
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
        if (!x || !y) return x + y;
        if (nd[x] < nd[y]) std::swap(x, y);
        rc(x) = merge(rc(x), y);
        if (nd[lc(x)].dist < nd[rc(x)].dist) std::swap(lc(x), rc(x));
        nd[x].dist = nd[rc(x)].dist + 1;
        return x;
    }

    int find(int x) {
        return nd[x].rt == x ? x : nd[x].rt = find(nd[x].rt);
    }
};
LeftTree<int> tr;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &tr.a[i]);
    }
    tr.init(n);
    while (m--) {
        int op, x;
        scanf("%d%d", &op, &x);
        if (op == 1) {
            int y;
            scanf("%d", &y);
            if (tr.nd[x].del || tr.nd[y].del) {
                continue;
            }
            x = tr.find(x); y = tr.find(y);
            if (x != y) tr.nd[x].rt = tr.nd[y].rt = tr.merge(x, y);
        } else {
            if (tr.nd[x].del) {
                puts("-1");
                continue;
            }
            x = tr.find(x);
            printf("%d\n", tr.nd[x].val);
            tr.nd[x].del = true;
            tr.nd[tr.lc(x)].rt = tr.nd[tr.rc(x)].rt = tr.nd[x].rt = tr.merge(tr.lc(x), tr.rc(x));
            tr.lc(x) = tr.rc(x) = tr.nd[x].dist = 0;
        }
    }
    return 0;
}