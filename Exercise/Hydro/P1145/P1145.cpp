// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <ctime>

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

int n, m;
const int maxn = 1e5 + 10;
struct Edge {
    int u, v;
}; std::vector<Edge> G[maxn];

int fa[maxn], son[maxn], dep[maxn], siz[maxn], top[maxn];;
void dfs1(int u) {
    son[u] = -1;
    siz[u] = 1;
    for (auto e : G[u]) {
        if (e.v != fa[u]) {
            fa[e.v] = u;
            dep[e.v] = dep[u] + 1;
            dfs1(e.v);
            siz[u] += siz[e.v];
            if (siz[son[u]] < siz[e.v]) son[u] = e.v;
        }
    }
}
void dfs2(int u, int tp) {
    top[u] = tp;
    if (son[u] == -1) return;
    dfs2(son[u], tp);
    for (auto e : G[u]) {
        if (e.v != fa[u] && e.v != son[u]) {
            dfs2(e.v, e.v);
        }
    }
}
int lca(int x, int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) std::swap(x, y);
    return x;
}

struct Tree {
    struct Node {
        int l, r, lc, rc;
        int max, maxcnt, sum;
    } nd[maxn << 6];
    int cnt;

    void init() {
        cnt = 0;
    }

    int crNode(int l, int r, int add = 0) {
        int id = ++cnt;
        nd[id].l = l; nd[id].r = r;
        nd[id].maxcnt = nd[id].sum = add;
        nd[id].max = l;
        nd[id].lc = nd[id].rc = -1;
        return id;
    }

    void upd(int a, int b, int c) {
        // return {a.l, b.r, lc, rc, a.cnt + b.cnt, a.sum + b.sum};
        nd[a].sum = nd[b].sum + nd[c].sum;
        nd[a].maxcnt = std::max(nd[b].maxcnt, nd[c].maxcnt);
        if (nd[b].maxcnt >= nd[c].maxcnt) {
            nd[a].max = nd[b].max;
        } else {
            nd[a].max = nd[c].max;
        }
    }

    void add(int u, int p, int c) {
        // writeln(u, nd[u].l, nd[u].r);
        if (nd[u].l == p && nd[u].r == p) {
            nd[u].sum += c;
            nd[u].maxcnt = nd[u].sum;
        } else {
            int mid = (nd[u].l + nd[u].r) >> 1;
            if (p <= mid) {
                if (nd[u].lc == -1) nd[u].lc = crNode(nd[u].l, mid);
                add(nd[u].lc, p, c);
            } else {
                if (nd[u].rc == -1) nd[u].rc = crNode(mid + 1, nd[u].r);
                add(nd[u].rc, p, c);
            }
            upd(u, nd[u].lc, nd[u].rc);
        }
    }

    void merge(int &a, int &b) {
        if (a == -1) { a = b; return;}
        if (b == -1) { return; }
        if (nd[a].l == nd[a].r) {
            nd[a].sum = nd[a].sum + nd[b].sum;
            // nd[a].cnt = nd[a].sum > 0;
            nd[a].maxcnt = nd[a].sum;
        } else {
            merge(nd[a].lc, nd[b].lc);
            merge(nd[a].rc, nd[b].rc);
            upd(a, nd[a].lc, nd[a].rc);
        }
    }
} tr;

int mp[maxn];
int ans[maxn];
std::vector<int> anslist;

int dfs(int u) {
    // writeln(u, tr.nd[mp[u]].sum);
    for (auto e : G[u]) {
        if (e.v != fa[u]) {
            int v = dfs(e.v);
            tr.merge(mp[u], v);
            // writeln(u, tr.nd[mp[u]].cnt);
        }
    }

    ans[u] = tr.nd[mp[u]].max;
    if (tr.nd[mp[u]].maxcnt == 0) ans[u] = 0;
    // writeln(u, tr.nd[mp[u]].sum);
    // if (ans < tr.nd[mp[u]].cnt) {
    //     ans = tr.nd[mp[u]].cnt;
    //     anslist.clear();
    //     anslist.push_back(u);
    // } else if (ans == tr.nd[mp[u]].cnt) {
    //     anslist.push_back(u);
    // }
    return mp[u];
}

int bg;

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        // freopen(".out", "w", stdout);
    #endif
    
    read(n, m);
    for (int i = 1; i < n; i++) {
        static int x, y;
        read(x, y);
        G[x].push_back({x, y});
        G[y].push_back({y, x});
    }

    dep[1] = 1; fa[1] = 1;
    dfs1(1);
    dfs2(1, 1);

    tr.init();
    for (int i = 1; i <= n; i++) {
        mp[i] = tr.crNode(1, 100000);
    }

    for (int i = 1; i <= m; i++) {
        int u, v, p;
        read(u, v, p);
        tr.add(mp[u], p, 1);
        tr.add(mp[v], p, 1);
        tr.add(mp[lca(u, v)], p, -1);
        if (lca(u, v) != 1) tr.add(mp[fa[lca(u, v)]], p, -1);
    }

    // writeln(tr.nd[mp[1]].sum);

    dfs(1);

    for (int i = 1; i <= n; i++) {
        writeln(ans[i]);
    }
    // std::sort(anslist.begin(), anslist.end());
    // writeln(anslist.size());
    // for (int i : anslist) {
    //     write(i); putchar(' ');
    // }
    return 0;
}
