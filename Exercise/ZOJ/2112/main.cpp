// Fhq %%%

#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <vector>

#define maxn 150001
template<typename T>
struct Fhq_Treap {
    struct TreeNode {
        int l, r;
        int rnd, size;
        T val;
        int rd() {
            return (rand() << 15 | rand());
        }
        TreeNode() {
            l = r = rnd = size = 0, val = 0;
        }
        TreeNode(T v) {
            l = 0;
            r = 0;
            val = v;
            size = 1;
            rnd = rd();
        }
    };

    #define lc(x) tr[x].l
    #define rc(x) tr[x].r

    // TreeNode tr[MAXN];
    std::vector<TreeNode> tr;
    int tot;
    int root;

    Fhq_Treap() {
        tot = 0;
        TreeNode tn;
        tr.push_back(tn);
    }

    void init() {
        tot = 0;
        TreeNode tn;
        tr.push_back(tn);
    }
    bool empty() const {
        return tot == 0;
    }
    int New(T val) {
        TreeNode tn(val);
        tr.push_back(tn);
        tr[++tot] = tn;
        return tot;
    }
    void update(int p) {
        tr[p].size = tr[lc(p)].size + tr[rc(p)].size + 1;
    }
    void split(int p, int &x, int &y, T val) {
        if (p == 0) {
            return void(x = y = 0);
        }
        // printf("split %d %lld %lld\n", p, tr[p].val, val);

        if (tr[p].val <= val) { // split at right
            // puts("LOL");
            x = p;
            split(rc(p), rc(p), y, val);
        } else {
            // puts("ROR");
            y = p;
            split(lc(p), x, lc(p), val);
        }
        update(p);
    }
    void merge(int &p, int x, int y) {
        if (!x || !y) { // some is zero
            return void(p = x + y);
        }

        if (tr[x].rnd > tr[y].rnd) {
            p = x;
            merge(tr[x].r, tr[x].r, y);
        } else {
            p = y;
            merge(tr[y].l, x, tr[y].l);
        }
        update(p);
    }

    int insert(T val) {
        if (empty()) {
            root = New(val);
        } else {
            int x, y;
            split(root, x, y, val - 1);
            merge(x, x, New(val));
            merge(root, x, y);
        }
        return 0;
    }
    int erase(T val) {
        if (empty()) {
            return -1;
        }
        int x, y, z;
        split(root, x, y, val);
        split(x, x, z, val - 1);
        merge(z, lc(z), rc(z));
        merge(x, x, z);
        merge(root, x, y);
        return 0;
    }
    int rnk_node_not_real(int node) { // return size of node + 1 and **its not real rnk**
        return tr[node].size + 1;
    }
    int rnk(T val, bool serious = true) {
        int x, y;
        split(root, x, y, val - 1);
        if (serious && tr[y].val != val) {
            return -1;
        }
        int ans = rnk_node_not_real(x);
        merge(root, x, y);
        return ans;
    }
    T kth(int k) {
        if (k > tot || k <= 0) {
            return -1;
        }
        int x = root;
        while (true) {         // hack ~~~.~  lc()
            if (k == rnk_node_not_real(lc(x))) return tr[x].val;
            if (k < rnk_node_not_real(lc(x))) x = lc(x);
            else k -= rnk_node_not_real(lc(x)), x = rc(x); // here - is because it go right
        }
    }
    T pre(T val) {
        int x, y;
        split(root, x, y, val - 1);
        if (x == 0) {
            merge(root, x, y);
            return -2147483647;
        }
        int pk = x;
        while (rc(pk)) pk = rc(pk);
        T ans = tr[pk].val;
        merge(root, x, y);
        return ans;
    }
    T suf(T val) {
        // printf("lol %d\n", root);
        // puts("suf");
        int x, y;
        split(root, x, y, val);
        if (y == 0) {
            merge(root, x, y);
            return 2147483647;
        }
        int pk = y;
        while (lc(pk)) pk = lc(pk);
        T ans = tr[pk].val;
        merge(root, x, y);
        return ans;
    }
};

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
template <typename T> struct segmt {
    struct TreeNode {
        int l, r;
        int lc, rc;
        Fhq_Treap<T> val;
    };

    TreeNode nd[maxn * 2];

    segmt() { tot = 0; }

    int a[maxn], tot;
    void init() { tot = 0; }
    int bt(int l, int r) {
        int id = ++tot;
        nd[id].l = l;
        nd[id].r = r;
        nd[id].val.init();
        for (int i = l; i <= r; i++) {
            nd[id].val.insert(a[i]);
        }

        if (l == r) {
            nd[id].lc = nd[id].rc = -1;
        } else {
            int mid = (l + r) >> 1;
            nd[id].lc = bt(l, mid);
            nd[id].rc = bt(mid + 1, r);
        }
        return id;
    }
    void change(int id, int pos, int x) {
        if (nd[id].l != nd[id].r) {
            int mid = nd[nd[id].lc].r;
            if (pos <= mid) {
                change(nd[id].lc, pos, x);
            } else {
                change(nd[id].rc, pos, x);
            }
        }
        nd[id].val.erase(a[pos]);
        nd[id].val.insert(x);
    }
    void change(int pos, int x) {
        change(1, pos, x);
        a[pos] = x;
    }
    int query_rnk(int id, int l, int r, T val) {
        if (nd[id].l == l && r == nd[id].r) {
            return nd[id].val.rnk(val, false) - 1;
        }

        if (r <= nd[nd[id].lc].r)
            return query_rnk(nd[id].lc, l, r, val);
        else if (l >= nd[nd[id].rc].l)
            return query_rnk(nd[id].rc, l, r, val);
        else
            return query_rnk(nd[id].lc, l, nd[nd[id].lc].r, val) +
                            query_rnk(nd[id].rc, nd[nd[id].rc].l, r, val);
    }
    T query_pre(int id, int l, int r, T val) {
        if (nd[id].l == l && r == nd[id].r) {
            return nd[id].val.pre(val);
        }

        if (r <= nd[nd[id].lc].r)
            return query_pre(nd[id].lc, l, r, val);
        else if (l >= nd[nd[id].rc].l)
            return query_pre(nd[id].rc, l, r, val);
        else
            return max(query_pre(nd[id].lc, l, nd[nd[id].lc].r, val), query_pre(nd[id].rc, nd[nd[id].rc].l, r, val));
    }
    T query_suf(int id, int l, int r, T val) {
        if (nd[id].l == l && r == nd[id].r) {
            return nd[id].val.suf(val);
        }

        if (r <= nd[nd[id].lc].r)
            return query_suf(nd[id].lc, l, r, val);
        else if (l >= nd[nd[id].rc].l)
            return query_suf(nd[id].rc, l, r, val);
        else
            return min(query_suf(nd[id].lc, l, nd[nd[id].lc].r, val), query_suf(nd[id].rc, nd[nd[id].rc].l, r, val));
    }
    T query_kth(int l, int r, int k) {
        T ll = 0, rr = 1e9 + 1;
        T ans;
        while (ll < rr) {
            T mid = (ll + rr) >> 1;
            int rnk = query_rnk(1, l, r, mid);
            if (rnk >= k) ans = mid, rr = mid - 1;
            else ll = mid + 1;
        }
        if (query_rnk(1, l, r, ans - 1) >= k) return ans - 2;
        else return ans - 1;
    }
};
segmt<int> tr;

int main() {
    // int T;
    // scanf("%d", &T);
    // while (T--) {
        tr.init();
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &tr.a[i]);
        }
        tr.bt(1, n);
        for (int i = 0; i < m; i++) {
            char ch[14];
            int l, r, k;
            scanf("%s%d%d", ch, &l, &r);
            
            if (ch[0] == 'C') {
                tr.change(l, r);
            } else {
                scanf("%d", &k);
                printf("%d\n", tr.query_kth(l, r, k));
            }
        }
    // }
    return 0;
}