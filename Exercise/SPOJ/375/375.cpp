#include <cstdio>
#include <cstring>
#include <vector>
// #pragma GCC optimize(fast)

#define int long long
#define maxn 100004

#define max(a, b) ((a) > (b) ? (a) : (b))
template <typename T> struct segmt {
    struct tree {
        int l, r, lc, rc;
        T ans, lazy2;
        T ansMax;
    } tr[4 * maxn];
    T a[maxn];
    int tot, n;
    inline void init(int nn) {
        tot = 0;
        n = nn;
        memset(a, 0, sizeof(int) * (n + 10));
    }
    inline int bt(int l, int r) {
        int pos = ++tot;
        tr[pos].l = l;
        tr[pos].r = r;
        tr[pos].lazy2 = 0;
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
        if (tr[pos].lazy2) {
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
    inline int query1(int pos, int l, int r) {
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
    inline int query2(int pos, int l, int r) {
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
segmt<int> sg;

struct Edge {
    int from, to, nxt, w, id;
};
Edge e[4 * maxn];
int head[maxn];
int EdgeToPoint[maxn];
int cnt = 0;
int n;
int Fa[maxn], Dep[maxn], Siz[maxn], Son[maxn], Top[maxn], dnk[maxn], rnk[maxn];
void init(int n) {
    memset(head, -1, sizeof(int) * (n + 10));
    // memset(EdgeToPoint, 0, sizeof(int) * (n + 10));
    // memset(Fa, 0, sizeof(int) * (n + 10));
    // memset(Dep, 0, sizeof(int) * (n + 10));
    // memset(Siz, 0, sizeof(int) * (n + 10));
    // memset(Son, 0, sizeof(int) * (n + 10));
    // memset(Top, 0, sizeof(int) * (n + 10));
    // memset(dnk, 0, sizeof(int) * (n + 10));
    // memset(rnk, 0, sizeof(int) * (n + 10));
    cnt = 0;
}
void insert(int from, int to, int wei, int id) {
    // e[cnt].from = from;
    e[cnt].to = to;
    e[cnt].nxt = head[from];
    e[cnt].w = wei;
    e[cnt].id = id;
    head[from] = cnt++;
}
void dfs1(int cur, int fa) {
    Fa[cur] = fa;
    Siz[cur] = 1;
    Son[cur] = -1;
    if (fa == -1) Dep[cur] = 0;
    else Dep[cur] = Dep[fa] + 1;
    for (int p = head[cur]; p != -1; p = e[p].nxt) {
        if (e[p].to == Fa[cur]) continue;
        dfs1(e[p].to, cur);
        if (Son[cur] == -1 || Siz[Son[cur]] < Siz[e[p].to]) {
            Son[cur] = e[p].to;
        }
        Siz[cur] += Siz[e[p].to];
        // puts("fk1");
    }
}
int tot;
void dfs2(int cur, int nowTop) {
    Top[cur] = nowTop;
    tot++;
    dnk[cur] = tot; rnk[tot] = cur;
    if (Son[cur] == -1) return;
    dfs2(Son[cur], nowTop);
    for (int p = head[cur]; p != -1; p = e[p].nxt) {
        if (e[p].to == Son[cur]) {
            sg.a[dnk[e[p].to]] = e[p].w;
            EdgeToPoint[e[p].id] = e[p].to;
        }
        if (e[p].to == Fa[cur] || e[p].to == Son[cur]) continue;
        dfs2(e[p].to, e[p].to);
        sg.a[dnk[e[p].to]] = e[p].w;
        EdgeToPoint[e[p].id] = e[p].to;
    }
}

signed main() {
    // freopen("P4114_10.in", "r", stdin);
    // freopen("P4114_10.ans", "w", stdout);
    int T = 1;
    // scanf("%lld", &T);
    while (T--) {
        int n;
        scanf("%lld", &n);
        sg.init(n);
        init(n);
        for (int i = 1; i < n; i++) {
            int x, y, w;
            scanf("%lld%lld%lld", &x, &y, &w);
            insert(x, y, w, i);
            insert(y, x, w, i);
        }
        puts("fk");
        dfs1(1, -1);
        tot = 0; dfs2(1, 1);
        sg.bt(1, n);
        while (true) {
            static char ch[1145]; int u, v;
            scanf("%s", ch);
            if (ch[0] == 'D') {
                break;
            } else {
                scanf("%lld%lld", &u, &v);
            }
            if (ch[0] == 'C') {
                sg.change(1, dnk[EdgeToPoint[u]], dnk[EdgeToPoint[u]], v);
            } else {
                int l = u, r = v;
                int maxx = 0;
                while (Top[l] != Top[r]) {
                    if (Dep[Top[l]] > Dep[Top[r]]) std::swap(l, r);
                    maxx = max(maxx, sg.query2(1, dnk[Top[r]], dnk[r]));
                    r = Fa[Top[r]];     
                } if (dnk[l] > dnk[r]) std::swap(l, r);
                // printf("%lld %lld\n", l, r);
                if (l == r) {
                    printf("%lld\n", maxx);
                    continue;
                }
                l = Son[l];
                if (l != -1) maxx = max(maxx, sg.query2(1, dnk[l], dnk[r]));
                printf("%lld\n", maxx);
            }
        }
    }
    return 0;
}