// Copyright 2023 Lotuses
#include <cmath>
#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

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

// #define int long long

const int maxn = 1e6 + 10;
int n, m, q;
int v[maxn], w[maxn], c[maxn];
std::vector<int> G[maxn];

// lca
int son[maxn], fa[maxn], dep[maxn], siz[maxn];
void dfs1(int u) {
    son[u] = -1; siz[u] = 1;
    for (int v : G[u]) {
        if (v != fa[u]) {
            fa[v] = u;
            dep[v] = dep[u] + 1;
            dfs1(v);
            siz[u] += siz[v];
            if (son[u] == -1 || siz[son[u]] < siz[v]) {
                son[u] = v;
            }
        }
    }
}
int top[maxn];
void dfs2(int u, int tp) {
    top[u] = tp;
    if (son[u] == -1) return;
    dfs2(son[u], tp);
    for (int v : G[u]) {
        if (v != son[u] && v != fa[u]) {
            dfs2(v, v);
        }
    }
}
int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) std::swap(u, v);
    return u;
}

// (()(()))
int lc[maxn], rc[maxn], kfn = 0;
int arr[maxn];
void dfs(int u) {
    lc[u] = ++kfn;
    arr[kfn] = u;
    for (int v : G[u]) {
        if (v != fa[u]) {
            dfs(v);
        }
    }
    rc[u] = ++kfn;
    arr[kfn] = u;
}

struct Op {
    int id, x;
} ch[maxn]; int tm = 0;
int BLOCK_SIZE;
struct Query {
    int l, r, t, id;
    bool operator < (const Query b) const {
        int kal = (l - 1) / BLOCK_SIZE + 1, kbl = (b.l - 1) / BLOCK_SIZE + 1;
        if (kal != kbl) return kal < kbl;
        int kar = (r - 1) / BLOCK_SIZE + 1, kbr = (b.r - 1) / BLOCK_SIZE + 1;
        if (kar != kbr) return kar < kbr;
        return t < b.t;
    }
} query[maxn]; int cntq = 0;

int l = 1, r = 0, t = 0;
int cntu[maxn], cntc[maxn];
long long ans = 0;
std::vector<int> cv[maxn];
void upd(int p, int x) {
    const int &u = arr[p];
    cntu[u] += x;
    // writeln(u, cntu[u]);
    if (cntu[u] == 2) {
        ans -= 1ll * w[cntc[c[u]]] * v[c[u]];
        cntc[c[u]]--;
    } else if (cntu[u] == 1) {
        cntc[c[u]]++;
        ans += 1ll * w[cntc[c[u]]] * v[c[u]];
    } else if (cntu[u] == 0 && x != 1) {
        ans -= 1ll * w[cntc[c[u]]] * v[c[u]];
        cntc[c[u]]--;
    } else {
        writeln(cntu[u]);
        exit(0);
        // assert(0);
    }
}
void updt(int tm, int x) {
    const Op &p = ch[tm];
    if (x == 1) {
        if (cntu[p.id] == 1) {
            ans -= 1ll * w[cntc[c[p.id]]] * v[c[p.id]];
            cntc[c[p.id]]--;
            c[p.id] = p.x;
            cntc[c[p.id]]++;
            ans += 1ll * w[cntc[c[p.id]]] * v[c[p.id]];
        } else {
            c[p.id] = p.x;
        }
        cv[p.id].push_back(p.x);
    } else {
        cv[p.id].pop_back();
        if (cntu[p.id] == 1) {
            ans -= 1ll * w[cntc[c[p.id]]] * v[c[p.id]];
            cntc[c[p.id]]--;
            c[p.id] = *cv[p.id].rbegin();
            cntc[c[p.id]]++;
            ans += 1ll * w[cntc[c[p.id]]] * v[c[p.id]];
        } else {
            c[p.id] = *cv[p.id].rbegin();
        }
    }
}

long long Ans[maxn];

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int x, y;
    read(n, m, q); BLOCK_SIZE = (int)(floor(pow(n, (double) 2 / 3)));
    for (int i = 1; i <= m; i++) read(v[i]);
    for (int i = 1; i <= n; i++) read(w[i]);
    for (int i = 1; i < n; i++) {
        read(x, y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    for (int i = 1; i <= n; i++) read(c[i]), cv[i].push_back(c[i]);

    fa[1] = 1; dep[1] = 0;
    dfs1(1);
    dfs2(1, 1);
    dfs(1);

    for (int i = 1; i <= q; i++) {
        int type;
        read(type, x, y);
        if (type == 0) {
            tm++;
            ch[tm] = {x, y};
        } else {
            if (lc[x] > lc[y]) std::swap(x, y);
            if (rc[x] > rc[y]) {
                query[++cntq] = {lc[x], lc[y], tm, cntq};
            } else {
                query[++cntq] = {rc[x], lc[y], tm, cntq};
            }
            if (x == y) {
                query[cntq].l = lc[x];
                query[cntq].r = lc[x];
            }
        }
    }

    std::sort(query + 1, query + cntq);

    upd(++r, 1);
    for (int i = 1; i <= cntq; i++) {
        Query &cq = query[i];
        // writeln(i, cq.t, cq.l, cq.r);
        while (t < cq.t) updt(++t, 1);
        while (l > cq.l) upd(--l, 1);
        while (r < cq.r) upd(++r, 1);
        while (t > cq.t) updt(t--, -1);
        while (l < cq.l) upd(l++, -1);
        while (r > cq.r) upd(r--, -1);
        long long lcaans = 0, lcaa = lca(arr[cq.l], arr[cq.r]);
        if (lcaa != arr[cq.l] && lcaa != arr[cq.r]) {
            lcaans = 1ll * w[cntc[c[lcaa]] + 1] * v[c[lcaa]];
        }  // /yiw
        Ans[cq.id] = ans + lcaans;
        // writeln(666, cq.id, c[cq.l], ans, lcaans);
    }

    for (int i = 1; i <= cntq; i++) {
        writeln(Ans[i]);
    }
    return 0;
}
