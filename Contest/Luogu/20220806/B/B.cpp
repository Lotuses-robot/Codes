// usage see BZOJ1036

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>

#define maxn 1000005
#define mod 998244353
#define max(a, b) ((a) < (b) ? (a) : (b))

struct Node {
    int p, id;
    bool operator < (Node b) const {
        return p < b.p;
    }
    Node operator + (Node b) const {
        return {(p + b.p) % mod, b.id};
    }
    Node operator = (int x) {
        p = x;
        return *this;
    }
    Node operator * (int k) const {
        return {p * k % mod, id};
    }
};

template <typename T> struct segmt {
    struct tree {
        int l, r, lc, rc;
        T ans, lazy2;
        T ansMax;
    } tr[2 * maxn];
    T a[maxn];
    int tot, n;
    segmt() {
        tot = 0;
        n = maxn / 2;
    }
    inline int bt(int l, int r) {
        int pos = ++tot;
        tr[pos].l = l;
        tr[pos].r = r;
        if (l == r) {
            tr[pos].lc = tr[pos].rc = -1;
            tr[pos].ans = a[l];
            tr[pos].ansMax = a[l];
        } else {
            tr[pos].lc = bt(l, l + r >> 1);
            tr[pos].rc = bt((l + r >> 1) + 1, r);
            tr[pos].ans = (tr[tr[pos].lc].ans + tr[tr[pos].rc].ans);
            tr[pos].ansMax = max(tr[tr[pos].lc].ansMax, tr[tr[pos].rc].ansMax);
        }
        return pos;
    }
    inline void update(int pos) {
        if (tr[pos].lazy2.p) {
            change(tr[pos].lc, tr[tr[pos].lc].l, tr[tr[pos].lc].r, tr[pos].lazy2);
            change(tr[pos].rc, tr[tr[pos].rc].l, tr[tr[pos].rc].r, tr[pos].lazy2);
            tr[pos].lazy2 = 0;
        }
        tr[pos].ans = (tr[tr[pos].lc].ans + tr[tr[pos].rc].ans);
        tr[pos].ansMax = max(tr[tr[pos].lc].ansMax, tr[tr[pos].rc].ansMax);
    }
    inline void change(int pos, int l, int r, T x) {
        if (tr[pos].l == l && tr[pos].r == r) {
            tr[pos].lazy2 = (tr[pos].lazy2 + x);
            tr[pos].ans = x * (r - l + 1);
            tr[pos].ansMax = x;
            return;
        }
        update(pos);
        if (r <= tr[tr[pos].lc].r)
            change(tr[pos].lc, l, r, x);
        else if (l >= tr[tr[pos].rc].l)
            change(tr[pos].rc, l, r, x);
        else {
            change(tr[pos].lc, l, tr[tr[pos].lc].r, x);
            change(tr[pos].rc, tr[tr[pos].rc].l, r, x);
        }
        tr[pos].ans = (tr[tr[pos].lc].ans + tr[tr[pos].rc].ans);
        tr[pos].ansMax = max(tr[tr[pos].lc].ansMax, tr[tr[pos].rc].ansMax);
    }
    inline T query1(int pos, int l, int r) {
        if (tr[pos].l == l && r == tr[pos].r)
            return tr[pos].ans;
        update(pos);
        if (r <= tr[tr[pos].lc].r)
            return query1(tr[pos].lc, l, r);
        else if (l >= tr[tr[pos].rc].l)
            return query1(tr[pos].rc, l, r);
        else
            return query1(tr[pos].lc, l, tr[tr[pos].lc].r) +
                            query1(tr[pos].rc, tr[tr[pos].rc].l, r);
    }
    inline T query2(int pos, int l, int r) {
        if (tr[pos].l == l && r == tr[pos].r)
            return tr[pos].ansMax;
        update(pos);
        if (r <= tr[tr[pos].lc].r)
            return query2(tr[pos].lc, l, r);
        else if (l >= tr[tr[pos].rc].l)
            return query2(tr[pos].rc, l, r);
        else
            return max(query2(tr[pos].lc, l, tr[tr[pos].lc].r), 
                            query2(tr[pos].rc, tr[tr[pos].rc].l, r));
    }
};
segmt<Node> sg;

struct Point {
    int x, y, ansY;
    bool operator < (const Point b) const {
        return y < b.y;
    }
};
struct Edge {
    Point a, b;
    bool operator < (const Edge q) const {
        return a.y < q.a.y;
    }
};
std::vector<Point> p;
std::vector<Edge> e;
std::map<std::pair<int, int>, int> mp;
std::map<std::pair<int, int>, int> tot;
void maintain() {
    std::sort(p.begin(), p.end());
    std::sort(e.begin(), e.end());
    int nowY = -1, pi = 0, ei = 0;
    while (pi < p.size() || ei < e.size()) {
        if ((p[pi].y <= e[ei].a.y || ei >= e.size()) && pi < p.size()) {
            auto pp = sg.query1(1, p[pi].x, p[pi].x);
            p[pi].ansY = pp.p;
            if (pp.p != 0) mp[std::make_pair(p[pi].x, p[pi].y)] = pp.id;
            else mp[std::make_pair(p[pi].x, p[pi].y)] = -1;
            pi++;
        } else {
            sg.change(1, e[ei].a.x, e[ei].b.x, {e[ei].a.y, ei});
            ei++;
        }
    }
}

int f[maxn], ppp[maxn];

int dfs(int x, int y, int eid) {
    int nxt = mp[std::make_pair(x, y)];
    if (nxt != -1 && f[nxt]) return f[nxt];
    int ans = 0;
    if (nxt == -1) ans = 1;
    else ans = dfs(e[nxt].a.x, e[nxt].a.y, nxt) + dfs(e[nxt].b.x, e[nxt].b.y, nxt);
    if (eid != -1) {
        f[eid] += ans;
    }
    return ans;
}

int main() {
    sg.n = 500000;
    sg.bt(0, sg.n);
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int l, r, h;
        scanf("%d%d%d", &l, &r, &h);
        p.push_back({l, h});
        p.push_back({r, h});
        e.push_back({{l, h}, {r, h}});
    }
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        if (!mp[std::make_pair(x, 1145141919)]) {
            p.push_back({x, 1145141919});
            ppp[i] = x;
        }
    }
    maintain();
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += dfs(ppp[i], 1145141919, -1);
        ans %= mod;
    }
    printf("%d\n", ans);
    return 0;
}