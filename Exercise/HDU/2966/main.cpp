#include <cstdio>
#include <cstring>
#include <algorithm>


#define int long long
int ind;

#define maxk 2
struct Point {
    int x[maxk];
    bool operator < (Point b) const {
        return x[ind] < b.x[ind];
    }
};

#define maxn 11451411

struct KdTree {
    Point a[maxn], p[maxn];
    void bt(int l, int r, int dep) {
        if (l > r) return;
        int mid = (l + r) >> 1;
        ind = dep % maxk;
        std::nth_element(a + l, a + mid, a + r + 1);
        bt(l, mid - 1, dep + 1);
        bt(mid + 1, r, dep + 1);
    }
    void bt(int n) {
        memcpy(p, a, sizeof(Point) * (n + 100));
        bt(1, n, 0);
    }
    
    #define pow2(x) (x) * (x)
    
    #define ll long long
    #define inf 1e18

    ll inds(Point a, Point b) {
        ll ret = 0;
        for (int i = 0; i < maxk; i++) {
            ret += pow2((ll)a.x[i] - b.x[i]);
        }
        return ret;
    }

    #define max(a, b) ((a) < (b) ? (a) : (b))

    int ans;

    void query(int l, int r, int dep, Point pt) {
        if (l > r) return;
        int mid = (l + r) >> 1;
        ind = dep % maxk;
        int dist = inds(a[mid], pt);
        if (!ans || (dist && dist < ans)) ans = dist;
        ll rr = pow2((ll)pt.x[ind] - a[mid].x[ind]);
        if (pt.x[ind] < a[mid].x[ind]) {
            query(l, mid - 1, dep + 1, pt);
            if (rr < ans) {
                query(mid + 1, r, dep + 1, pt);
            }
        } else {
            query(mid + 1, r, dep + 1, pt);
            if (rr < ans) {
                query(l, mid - 1, dep + 1, pt);
            }
        }
    }
    ll query(int n, Point pt) {
        ans = 0;
        query(1, n, 0, pt);
        return ans;
    }
}tr;

signed main() {
    // freopen("data/1.in", "r", stdin);
    // freopen(".out", "w", stdout);
    int T;
    scanf("%lld", &T);

    while (T--) {
        int n;
        scanf("%lld", &n);
        for (int i = 1; i <= n; i++) {
            int x, y;
            scanf("%lld%lld", &x, &y);
            tr.a[i].x[0] = x;
            tr.a[i].x[1] = y;
        }
        tr.bt(n);
        for (int i = 1; i <= n; i++) {
            printf("%lld\n", tr.query(n, tr.p[i]));
        }
    }
    return 0;
}