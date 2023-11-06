// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <vector>
// #include <map>
// #include <set>
// #include <list>
// #include <queue>
// #include <stack>
// #include <string>
// #include <random>
// #include <algorithm>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

template<typename T>
void read(T &r) { r = 0; static char ch, last; ch = getchar(), last = 'z'; while (ch < '0' || ch > '9') last = ch, ch = getchar(); while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = getchar(); r = (last == '-') ? -r : r; }
template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) { read(arg); read(arg_left...); }

template<typename T>
void write(T x) { if (x < 0) putchar('-'), x = -x; int len = 0; static char ch[100]; while (x) ch[++len] = x % 10 + '0', x /= 10; if (!len) ch[++len] = '0'; while (len) putchar(ch[len--]); }
template<typename T, typename...Ts>
void write(T arg, Ts...arg_left) { write(arg); putchar(' '); write(arg_left...); }
template<typename T>
void writeln(T x) { write(x); putchar('\n'); }
template<typename T, typename...Ts>
void writeln(T arg, Ts...arg_left) { write(arg); putchar(' '); write(arg_left...); putchar('\n'); }

// #define __DEBUG
#ifdef __DEBUG
#define debug(arg, args...) { printf("db <%d> ", __LINE__); writeln(arg, ##args); }
#else
#define debug(arg, args...) {}
#endif
#define ins(a, b) (G[a].emplace_back(b))

#define int long long

const int maxn = 2e5 + 10, infx = 0x3f3f3f3f;
int n, q, k;
int val[maxn], a[maxn];
std::vector<int> G[maxn];

struct Mat {
    int f[3][3];
    Mat() { memset(f, 63, sizeof(f)); }
    void init() { memset(f, 63, sizeof(f)); }
    Mat operator * (const Mat b) const {
        Mat c;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    c.f[i][j] = std::min(c.f[i][j], f[i][k] + b.f[k][j]);
                }
            }
        }
        return c;
    }
    void print() const {
        puts("-------------");
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                write(f[i][j]); putchar(' ');
            }
            puts("");
        }
        puts("#############");
    }
} lm, rm;

void initMat(Mat &m, int u) {
    m.init();
    if (k == 1) {
        m.f[0][0] = val[u];
    } else if (k == 2) {
        m.f[0][0] = m.f[1][0] = val[u];
        m.f[0][1] = 0;
    } else if (k == 3) {
        m.f[0][0] = m.f[1][0] = m.f[2][0] = val[u];
        m.f[0][1] = 0; m.f[1][1] = a[u]; m.f[2][1] = a[u] + val[u];
        m.f[0][2] = m.f[1][2] = 0;
    }
}

int siz[maxn], son[maxn], fa[maxn], dep[maxn];
void dfs1(int u, int f) {
    fa[u] = f; dep[u] = dep[f] + 1;
    siz[u] = 1; son[u] = 0;
    for (int v : G[u]) {
        if (v != f) {
            dfs1(v, u);
            siz[u] += siz[v];
            if (!son[u] || siz[v] > siz[son[u]]) {
                son[u] = v;
            }
        }
    }
}

int dfn[maxn], rnk[maxn], top[maxn], idx = 0;
void dfs2(int u, int tp) {
    top[u] = tp;
    dfn[u] = ++idx; rnk[idx] = u;
    if (son[u]) dfs2(son[u], tp);
    for (int v : G[u]) {
        if (v != son[u] && v != fa[u]) {
            dfs2(v, v);
        }
    }
}

struct Tree {
    struct Node {
        int l, r, lc, rc;
        Mat x;
    } nd[maxn << 2];
    int cnt;

    void init() {
        cnt = 0;
    }
    int bt(int l, int r) {
        int u = ++cnt;
        nd[u].l = l; nd[u].r = r;
        nd[u].lc = nd[u].rc = -1;
        if (l == r) {
            initMat(nd[u].x, rnk[l]);
        } else {
            int mid = (l + r) >> 1;
            nd[u].lc = bt(l, mid);
            nd[u].rc = bt(mid + 1, r);
            nd[u].x = nd[nd[u].rc].x * nd[nd[u].lc].x;
        }
        return u;
    }

    Mat query(int u, int l, int r) const {
        // if (l > r) return 
        if (nd[u].l == l && nd[u].r == r) {
            return nd[u].x;
        } else {
            int mid = (nd[u].l + nd[u].r) >> 1;
            if (r <= mid) return query(nd[u].lc, l, r);
            else if (l > mid) return query(nd[u].rc, l, r);
            else {
                return query(nd[u].rc, mid + 1, r) * query(nd[u].lc, l, mid);
            }
        }
    }
} tr;

int query(int l, int r) {
    while (top[l] != top[r]) {
        if (dep[top[l]] < dep[top[r]]) std::swap(l, r);
        l = fa[top[l]];
    }
    if (dep[l] > dep[r]) return r;
    return l;
}

int solve(int lca) {
    int ans = lm.f[0][0] + rm.f[0][0] - val[lca];
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            if (i + j <= k) {
                ans = std::min(ans, lm.f[0][i] + rm.f[0][j]);
                // writeln(lm.f[0][i], rm.f[0][j]);
            }
        }
    }
    return ans;
}

void add(int u, int p, Mat &m) {
    m.init();
    if (u == p) {
        m.f[0][0] = val[u];
        return;
    }
    m.f[0][0] = val[u];
    if (k == 3) m.f[0][1] = val[u] + a[u];
    u = fa[u];
    while (top[u] != top[p]) {
        m = m * tr.query(1, dfn[top[u]], dfn[u]);
        // writeln(m.f[0][0], m.f[0][1], m.f[0][2]);
        u = fa[top[u]];
        // writeln(u);
    }
    m = m * tr.query(1, dfn[p], dfn[u]);
    // writeln(m.f[0][0], m.f[0][1], m.f[0][2]);
}

tsz main() {
    #ifdef LOCAL
        freopen("data/transmit4.in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, q, k);
    for (int i = 1; i <= n; i++) {
        read(val[i]);
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        read(u, v);
        ins(u, v);
        ins(v, u);
    }
    for (int u = 1; u <= n; u++) {
        a[u] = infx;
        for (int v : G[u]) {
            a[u] = std::min(a[u], val[v]);
        }
    }
    
    dep[1] = 0; dfs1(1, 1);
    dfs2(1, 1);
    tr.init(); tr.bt(1, n);

    while (q--) {
        int s, t;
        read(s, t);
        int l = query(s, t);
        // writeln(l);
        add(s, l, lm);
        add(t, l, rm);
        writeln(solve(l));
    }
    return 0;
}