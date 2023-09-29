// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>

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
#define debug(arg, args...) { printf("d <%d> ", __LINE__); writeln(arg, ##args); }
#else
#define debug(arg, args...) {}
#endif

const int maxn = int(1e5 + 10) << 6;
int p[maxn], fa[maxn], rt[maxn];

int findfa(int u) {
    if (fa[u] == u) return u;
    return fa[u] = findfa(fa[u]);
}

struct segt {
    struct Node {
        int l, r, lc, rc;
        int cnt, id;
    } nd[maxn];
    int cnt, R;
    void init(int _R) { cnt = 0; R = _R; }
    int cr(int l, int r) {
        int id = ++cnt;
        nd[cnt].l = l; nd[cnt].r = r;
        nd[cnt].lc = nd[cnt].rc = -1;
        nd[cnt].cnt = 0;
        return id;
    }
    int autocr(int &u, int l, int r) {
        if (u == -1) {
            u = cr(l, r);
        }
        return u;
    }
    void upd(int u) {
        nd[u].cnt = 0;
        if (~nd[u].lc) nd[u].cnt += nd[nd[u].lc].cnt;
        if (~nd[u].rc) nd[u].cnt += nd[nd[u].rc].cnt;
    }
    void ins(int u, int x, int id) {
        int l = nd[u].l, r = nd[u].r;
        if (l == x && r == x) {
            nd[u].cnt++;
            nd[u].id = id;
        } else {
            int mid = (l + r) >> 1;
            if (x <= mid) ins(autocr(nd[u].lc, l, mid), x, id);
            else ins(autocr(nd[u].rc, mid + 1, r), x, id);
            upd(u);
        }
    }
    int bt(int val, int id) {
        int rt = cr(1, R);
        ins(rt, val, id);
        return rt;
    }
    void merge(int &l, int &r) {
        if (!(~l)) { l = r; r = 0; return; }
        if (!(~r)) return;
        if (nd[l].l == nd[l].r) {
            nd[l].cnt += nd[r].cnt;
        } else {
            merge(nd[l].lc, nd[r].lc);
            merge(nd[l].rc, nd[r].rc);
            upd(l);
        }
    }
    int query(int u, int x) {
        // printf("query %d %d %d %d\n", u, nd[u].lc, nd[nd[u].lc].cnt, nd[u].rc);
        if (nd[u].l == nd[u].r) return nd[u].id;
        if (nd[u].lc != -1 && nd[nd[u].lc].cnt >= x) {
            return query(nd[u].lc, x);
        } else {
            if (nd[u].lc != -1) x -= nd[nd[u].lc].cnt;
            return query(nd[u].rc, x);
        }
    }
} tr;

int ch[10];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        // freopen(".out", "w", stdout);
    #endif
    
    int n, m;
    read(n, m);
    tr.init(n);
    for (int i = 1; i <= n; i++) {
        read(p[i]);
        fa[i] = i;
        rt[i] = tr.bt(p[i], i);
        // writeln(tr.query(rt[i], 1));
    }
    for (int i = 1; i <= m; i++) {
        int u, v, uf, vf;
        read(u, v);
        uf = findfa(u); vf = findfa(v);
        if (uf != vf) {
            fa[vf] = uf;
            // writeln(rt[uf], rt[vf]);
            tr.merge(rt[uf], rt[vf]);
        }
    }
    int T, x, y, fx, fy;
    read(T);
    while (T--) {
        scanf("%s", ch);
        read(x, y);
        if (ch[0] == 'B') {
            fx = findfa(x); fy = findfa(y);
            if (fx != fy) {
                fa[fy] = fx;
                // writeln(rt[fx], rt[fy]);
                tr.merge(rt[fx], rt[fy]);
                // writeln(tr.nd[rt[fx]].cnt);
            }
        } else {
            fx = findfa(x);
            // writeln(rt[fx]);
            if (y > tr.nd[rt[fx]].cnt) puts("-1");
            else writeln(tr.query(rt[fx], y));
        }
    }
    
}
