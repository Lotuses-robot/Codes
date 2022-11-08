#include <cstdio>
#include <ctime>
#include <cstdlib>

#define ll long long
#define MAXN 1145141
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

    TreeNode tr[maxn];
    int tot;
    int root;

    Fhq_Treap() { tot = 0; }

    void init() {
        tot = 0;
    }
    bool empty() const {
        return tot == 0 || root == 0;
    }
    int New(T val) {
        TreeNode tn(val);
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
            return -1;
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
            return -1;
        }
        int pk = y;
        while (lc(pk)) pk = lc(pk);
        T ans = tr[pk].val;
        merge(root, x, y);
        return ans;
    }
};
Fhq_Treap<ll> treap;

int main() {
    // freopen("data/2.in", "r", stdin);
    // freopen("main.out", "w", stdout);
    int n, ins = 0, tot = 0;
    ll min, add = 0;
    scanf("%d%d", &n, &min);

    for (int i = 0; i < n; i++) {
        char ch[114]; int k;
        scanf("%s%d", ch, &k);
        if (ch[0] == 'I') {
            if (k - add >= min) {
                treap.insert(k - add);
                ins++;
            }
        } else if (ch[0] == 'A') {
            min -= k; add += k;
        } else if (ch[0] == 'S') {
            min += k; add -= k;
            while (!treap.empty() && treap.kth(1) < min) {
                // printf("%d\n", treap.kth(1));
                treap.erase(treap.kth(1));
                ins--; tot++;
            }
        } else if (ch[0] == 'F') {
            if (k > ins) {
                puts("-1");
            } else {
                printf("%lld\n", treap.kth(ins - k + 1) + add);
            }
        }
    }
    printf("%d\n", tot);
    return 0;
}