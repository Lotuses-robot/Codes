#include <cstdio>
#include <cstring>
#include <vector>

// map
#define maxn 1000006
struct Edge {
    int from, to, nxt, w;
};
Edge e[2 * maxn];
int head[maxn], weight[maxn];
int cnt = 0;
int n;

void init() {
    cnt = 0;
    // memset(weight, 0, sizeof(weight));
    memset(head, -1, sizeof(head));
}

void insert(int from, int to, int wei) {
    e[cnt].from = from;
    e[cnt].to = to;
    e[cnt].nxt = head[from];
    e[cnt].w = wei;
    head[from] = cnt++;
}

int Fa[maxn], Dep[maxn], Siz[maxn], Son[maxn];
void dfs1(int cur, int fa) {
    Fa[cur] = fa;
    Siz[cur] = 1;
    if (fa == -1) Dep[cur] = 0;
    else Dep[cur] = Dep[Fa[cur]] + 1;
    int maxx = -1, maxid = -1;
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
    for (int p = head[cur]; p != -1; p = e[p].nxt) {
        if (e[p].to != Fa[cur]) weight[e[p].to] = weight[cur] + e[p].w;
        if (e[p].to == Fa[cur] || e[p].to == Son[cur]) continue;
        dfs2(e[p].to, e[p].to);
    }
    dfs2(Son[cur], nowTop);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        init();
        int m, root;
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n - 1; i++) {
            int x, y, w;
            scanf("%d%d%d", &x, &y, &w);
            insert(x, y, w);
            insert(y, x, w);
            root = x;
        }
        dfs1(root, -1);
        tot = 0; dfs2(root, root);
        while (m--) {
            int yl, yr;
            scanf("%d%d", &yl, &yr);
            int l = yl, r = yr;
            while (Top[l] != Top[r]) {
                if (Dep[Top[l]] > Dep[Top[r]]) {
                    std::swap(l, r);
                }
                // change r
                r = Fa[Top[r]];
            }
            if (Dep[l] > Dep[r]) {
                std::swap(l, r);
            }
            int LCA = l;
            int dist = weight[yl] + weight[yr] - 2 * weight[LCA];
            printf("%d\n", dist);
        }
    }
    return 0;
}