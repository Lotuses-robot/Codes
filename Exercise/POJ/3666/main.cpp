#include <cstdio>
#include <utility>

#define maxn 114514

template<typename T>
struct LeftTree {
    struct TreeNode {
        int id, l, r, rt, dist, sz;
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
            nd[i].sz = 1;
        }
        nd[0].dist = -1;
    }

    int merge(int x, int y) {
        if (!x || !y) return x + y;
        if (nd[x] < nd[y]) std::swap(x, y);
        rc(x) = merge(rc(x), y);
        if (nd[lc(x)].dist < nd[rc(x)].dist) std::swap(lc(x), rc(x));
        nd[x].dist = nd[rc(x)].dist + 1;
        nd[x].sz = nd[lc(x)].sz + nd[rc(x)].sz + 1;
        return x;
    }

    int find(int x) {
        return nd[x].rt == x ? x : nd[x].rt = find(nd[x].rt);
    }

    void pop(int& x) {
        x = find(x);
        x = merge(lc(x), rc(x));
    }
};
LeftTree<int> tr;
int root[maxn];
int num[maxn];

#define abs(x) ((x) < 0 ? -(x) : (x))

int main() {
    int n, m;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &tr.a[i]);
    }
    tr.init(n);
    
    int cnt = 0, ans = 0, lastrt = 0;
    for (int i = 1; i <= n; i++) {
        root[++cnt] = i;   
        num[cnt] = 1;
        while (cnt > 1 && tr.nd[root[cnt]].val < tr.nd[root[cnt - 1]].val) {
            cnt--;
            root[cnt] = tr.merge(root[cnt], root[cnt + 1]);
            num[cnt] += num[cnt + 1];
            if (tr.nd[root[cnt]].sz * 2 > num[cnt] + 1) tr.pop(root[cnt]);
        }
    }
    int k = 0;
    for (int i = 1; i <= cnt; i++) {
        for (int j = 0, x = tr.nd[root[i]].val; j < num[i]; j++) {
            ans += abs(tr.a[++k] - x);
        }
    }
    printf("%d\n", ans);
    return 0;
}