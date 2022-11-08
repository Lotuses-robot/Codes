#include <cstdio>
#include <queue>

#define MAXN 1145141
template<typename T>
struct Splay {
    struct TreeNode {
        int ch[2];
        int size, tot, fa;
        T val;
        TreeNode() {
            fa = ch[0] = ch[1] = size = 0, val = 0, tot = 0;
        }
        TreeNode(T v) {
            fa = 0;
            ch[0] = ch[1] = 0;
            val = v;
            size = 1;
            tot = 1;
        }
    };

    TreeNode tr[maxn];
    int tot;
    int root, err;

    #define lc(x) tr[x].ch[0]
    #define rc(x) tr[x].ch[1]
    #define fa(x) tr[x].fa
    #define get(p) (rc(fa(p)) == p)


    Splay() { tot = 0; err = 0; }

    void init() {
        err = 0;
        tot = 0; root = 0;
    }
    bool empty() const {
        return root == 0;
    }
    int New(T val) {
        TreeNode tn(val);
        tr[++tot] = tn;
        return tot;
    }
    void Del(int p) {
        TreeNode tn;
        tr[p] = tn;
        err++;
    }
    void update(int p) {
        tr[p].size = tr[lc(p)].size + tr[rc(p)].size + tr[p].tot;
    }
    void rotate(int p) {
        int lo = get(p), f = fa(p),
            lof = get(f), ff = fa(f);
        tr[f].ch[lo] = tr[p].ch[lo ^ 1];
        if (tr[p].ch[lo ^ 1]) fa(tr[p].ch[lo ^ 1]) = f;
        tr[p].ch[lo ^ 1] = f;
        fa(f) = p;
        fa(p) = ff;
        if (ff) tr[ff].ch[lof] = p;
        update(f);
        update(p);
    }
    void play(int p, int to) {
        int end = fa(to);
        while (fa(p) != end) {
            if (fa(fa(p)) == end) rotate(p);
            else if (get(p) == get(fa(p))) rotate(fa(p)), rotate(p);
            else rotate(p), rotate(p);
        }
        if (to == root) {
            root = p;
        }
    }

    void insert(T val) {
        if (empty()) {
            root = New(val);
            return;
        }
        int p = root, f = 0;
        while (true) {
            if (tr[p].val == val) {
                tr[p].tot++;
                update(p);
                update(f);
                play(p, root);
                return;
            }
            f = p;
            p = tr[p].ch[tr[p].val < val];
            if (!p) {
                int NewPoint;
                NewPoint = tr[f].ch[tr[f].val < val] = New(val);
                fa(NewPoint) = f;
                update(NewPoint);
                update(f);
                play(NewPoint, root);
                return;
            }
        }
    } 
    int rnk(T val) {
        if (empty()) {
            return -1;
        }
        int p = root, res = 0;
        while (true) {
            if (tr[p].val == val) {
                res += tr[lc(p)].size;
                play(p, root);
                return res + 1;
            }
            if (tr[p].val > val) { // go left
                p = lc(p);
            } else {               // go right
                res += tr[lc(p)].size;
                res += tr[p].tot;
                p = rc(p);
            }
            if (!p) return -1;
        }
    }
    T kth(int k, bool secu = false) {
        if (secu && (k <= 0 || k > tot - err)) return -1;
        int p = root;
        bool flag = false;
        while (true) {
            if (lc(p) && k <= tr[lc(p)].size) { // must go left
                p = lc(p);
            } else {
                k -= tr[p].tot + tr[lc(p)].size;
                if (k <= 0) {
                    play(p, root);
                    return tr[p].val;
                }
                p = rc(p);
            }
        }
    }
    T pre(T val) {
        int p = lc(root);
        if (!p) return -1;
        while (rc(p)) p = rc(p);
        play(p, root);
        return tr[p].val;
    }
    T suf(T val) {
        int p = rc(root);
        if (!p) return -1;
        while (lc(p)) p = lc(p);
        play(p, root);
        return tr[p].val;
    }
    int erase(T val) {
        int ret = rnk(val);
        if (ret == -1) return -1;
        if (tr[root].tot > 1) {
            tr[root].tot--;
            update(root);
            return 0;
        }
        if (!lc(root) && !rc(root)) {
            Del(root);
            root = 0;
            return 0;
        }
        if (!lc(root)) {
            int p = rc(root);
            Del(root);
            root = p;
            fa(p) = 0;
            return 0;
        }
        if (!rc(root)) {
            int p = lc(root);
            Del(root);
            root = p;
            fa(p) = 0;
            return 0;
        }
        int p = root;
        int x = pre(val);
        fa(rc(p)) = root;
        rc(root) = rc(p);
        Del(p);
        update(root);
        return 0;
    }
};
Splay<int> sp;

std::queue<int> q;

int totWrong = 0;
int checkTree(int p) {
    int ans = sp.tr[p].tot;
    if (sp.lc(p)) {
        ans += checkTree(sp.lc(p));
    }
    if (sp.rc(p)) {
        ans += checkTree(sp.rc(p));
    }
    if (sp.tr[p].size != ans) {
        totWrong++;
    }
    return ans;
}

int main() {
    freopen("data/8.in", "r", stdin);
    freopen("main.out", "w", stdout);
    int T, tot = 0;
    scanf("%d", &T);
    while (T--) {
        int opt, x;
        scanf("%d%d", &opt, &x);
        // printf("haha %d %d\n", ++tot, opt);

        if (opt == 1) {
            sp.insert(x);
        } else if (opt == 2) {
            sp.erase(x);
        } else if (opt == 3) {
            // ++tot;
            // puts("3");
            printf("%d\n", sp.rnk(x));
        } else if (opt == 4) {
            // ++tot;
            // puts("4");
            printf("%d\n", sp.kth(x));
        } else if (opt == 5) {
            // ++tot;
            // puts("5");
            sp.insert(x);
            printf("%d\n", sp.pre(x));
            sp.erase(x);
        } else if (opt == 6) {
            // ++tot;
            // puts("6");
            sp.insert(x);
            printf("%d\n", sp.suf(x));
            sp.erase(x);
        }
        // totWrong = 0;
        // checkTree(sp.root);
        // printf("%d %d %d\n", ++tot, totWrong, sp.tr[0].size);
    }
    return 0;
}