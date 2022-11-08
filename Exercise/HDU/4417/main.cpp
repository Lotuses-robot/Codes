#include <cstdio>
#include <cstring>
#include <map>
#include <vector>

#define maxn 200010

template<typename T>
struct seg {
    struct TreeNode {
        int l, r;
        int lc, rc;
        int cnt;
        TreeNode() { l = r = lc = rc = cnt = 0; }
    };
    // std::vector<int> hrt;
    // std::vector<TreeNode> tn;
    int hrt[maxn * 6];  int tot1;
    TreeNode tn[maxn * 6];  int tot2;

    int New() {
        // tn.push_back(TreeNode());
        tn[tot1++] = TreeNode();
        return tot1 - 1;
    }
    int NewHist() {
        hrt[tot2++] = 0;
        return tot2 - 1;
    }
    void init() {
        // tn.clear(); hrt.clear();
        tot1 = tot2 = 0;
        New();
        NewHist();
    }
    void build(int &p, int l, int r) {
        p = New();
        tn[p].l = l; tn[p].r = r;
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(tn[p].lc, l, mid);
        build(tn[p].rc, mid + 1, r);
    }
    void insert(int origp, int& newp, int l, int r, int v) {
        newp = New();
        tn[newp] = tn[origp];
        tn[newp].cnt++;
        if (l == r) return;
        int mid = (l + r) >> 1;
        if (v <= mid) {
            insert(tn[origp].lc, tn[newp].lc, l, mid, v);
        } else {
            insert(tn[origp].rc, tn[newp].rc, mid + 1, r, v);
        }
    }
    int query(int x, int y, int l, int r, int k) {
        if (l == r) return l;
        int mid = (l + r) >> 1;
        int rnk = tn[tn[y].lc].cnt - tn[tn[x].lc].cnt;
        // printf("debug %d %d %d %d\n", l, r, rnk, k);
        if (k <= rnk) { // to left
            return query(tn[x].lc, tn[y].lc, l, mid, k);
        } else {
            return query(tn[x].rc, tn[y].rc, mid + 1, r, k - rnk);
        }
    }
};
seg<int> segt;
std::map<int, int> mp;
int pm[maxn];

int a[maxn];

int main() {
    int T;
    scanf("%d", &T);
    for (int TTT = 1; TTT <= T; TTT++) {
        mp.clear();
        segt.init();
        memset(pm, 0, sizeof(pm));

        int n, m;
        scanf("%d%d", &n, &m);

        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            mp[a[i]] = 1;
        }

        int rnk = 0;

        for (std::map<int, int>::iterator p = mp.begin(); p != mp.end(); p++) {
            // printf("%d ", p.first);
            if (p -> second) mp[p -> first] = ++rnk;
            pm[rnk] = p -> first;
            // puts("fk");
        }
        // puts("");

        segt.init();
        segt.build(segt.hrt[1], 1, rnk);

        for (int i = 0; i < n; i++) {
            int nowId = segt.NewHist();
            segt.insert(segt.hrt[nowId - 1], segt.hrt[nowId], 1, rnk, mp[a[i]]);
        }

        printf("Case %d:\n", TTT);
        for (int i = 0; i < m; i++) {
            int l, r, q;
            scanf("%d%d%d", &l, &r, &q);
            l++; r++;
            int ll = 0, rr = 1000001000;
            while (ll + 1 < rr) {
                int k = (ll + rr) >> 1;
                int ans = pm[segt.query(segt.hrt[l - 1], segt.hrt[r], 1, rnk, k)];
                if (ans <= q) { 
                    ll = k;
                } else {
                    rr = k - 1;
                }
            }
            int k = ll;
            int ans = pm[segt.query(segt.hrt[l - 1], segt.hrt[r], 1, rnk, k)];
            if (ans == q) {
                printf("%d\n", ll);
            } else {
                printf("%d\n", rr);
            }
        }
    }
    return 0;
}