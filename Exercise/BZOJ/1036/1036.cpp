#include <cstdio>
#include <cstring>
#include <vector>

// map
#define maxn 1000006
struct Edge {
    int from, to, nxt;
};
Edge e[2 * maxn];
int head[maxn];
int cnt = 0;
int n;
void init() {
    memset(head, -1, sizeof(head));
    cnt = 0;
}
void insert(int from, int to) {
    e[cnt].from = from;
    e[cnt].to = to;
    e[cnt].nxt = head[from];
    head[from] = cnt++;
}
int Fa[maxn], Dep[maxn], Siz[maxn], Son[maxn];
void dfs1(int cur, int fa) {
    Fa[cur] = fa;
    Siz[cur] = 1;
    if (fa == -1) Dep[cur] = 0;
    else Dep[cur] = Dep[fa] + 1;
    int maxx = 0, maxid = -1;
    for (int p = head[cur]; p != -1; p = e[p].nxt) {
        if (e[p].to == Fa[cur]) continue;
        dfs1(e[p].to, cur);
        if (maxx < Siz[e[p].to]) {
            maxx = Siz[e[p].to];
            maxid = e[p].to;
        }
        Siz[cur] += Siz[e[p].to];
    }
    Son[cur] = maxid;
}
int Top[maxn], dnk[maxn], rnk[maxn];
//             ^^^--------^^^------ start from 1
int tot;
void dfs2(int cur, int nowTop) {
    Top[cur] = nowTop;
    tot++;
    dnk[cur] = tot; rnk[tot] = cur;
    if (Son[cur] == -1) return;
    dfs2(Son[cur], nowTop);
    for (int p = head[cur]; p != -1; p = e[p].nxt) {
        if (e[p].to == Fa[cur] || e[p].to == Son[cur]) continue;
        dfs2(e[p].to, e[p].to);
    }
}

#define max(a, b) ((a) > (b) ? (a) : (b))
template <typename T> struct segmt {
    struct tree {
        int l, r, lc, rc;
        T ans, lazy2;
        T ansMax;
    } tr[2 * maxn];
    T a[maxn];
    int tot, n;
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

int main() {
    int n;
    scanf("%d", &n);
    sg.n = n;
    init();
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        insert(x, y);
        insert(y, x);
    }
    dfs1(1, -1);
    tot = 0; dfs2(1, 1);
    // for (int i = 1; i <= n; i++) {
    //     printf("%d ", dnk[i]);
    // }
    // puts("");
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        sg.a[dnk[i]] = x;
    }
    sg.bt(1, n);
    int q;
    scanf("%d", &q);
    while (q--) {
        static char ch[1145]; int u, v;
        scanf("%s%d%d", &ch, &u, &v);
        if (ch[0] == 'C') {
            sg.change(1, dnk[u], dnk[u], v);
        } else {
            if (ch[1] == 'M') {
                int l = u, r = v;
                int maxx = -1145141919;
                while (Top[l] != Top[r]) {
                    if (Dep[Top[l]] > Dep[Top[r]]) std::swap(l, r);
                    maxx = max(maxx, sg.query2(1, dnk[Top[r]], dnk[r]));
                    r = Fa[Top[r]];     
                } if (dnk[l] > dnk[r]) std::swap(l, r);
                // printf("%d %d\n", l, r);
                maxx = max(maxx, sg.query2(1, dnk[l], dnk[r]));
                printf("%d\n", maxx);
            } else {
                int l = u, r = v;
                int sum = 0;
                while (Top[l] != Top[r]) {
                    if (Dep[Top[l]] > Dep[Top[r]]) std::swap(l, r);
                    sum += sg.query1(1, dnk[Top[r]], dnk[r]);
                    // printf("%d %d %d %d %d\n", l, r, Top[r], Fa[Top[r]], sg.query1(1, dnk[Top[r]], dnk[r]));
                    r = Fa[Top[r]];
                } if (dnk[l] > dnk[r]) std::swap(l, r);
                // printf("%d %d %d\n", dnk[l], dnk[r], sg.query1(1, dnk[l], dnk[r]));
                sum += sg.query1(1, dnk[l], dnk[r]);
                printf("%d\n", sum);
            }
        }
    }
    return 0;
}