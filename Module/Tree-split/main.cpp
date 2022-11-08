// usage see BZOJ1036

#include <cstdio>
#include <cstring>
#include <vector>

// map
#define maxn 1000006
struct Edge {
    int from, to, nxt, w;
};
Edge e[2 * maxn];
int head[maxn];
int cnt = 0;
int n;
int pw[maxn], peid[maxn], epid[maxn];

void init() {
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
    else Dep[cur] = Dep[fa] + 1;
    int maxx = 0, maxid = -1;
    for (int p = head[cur]; p != -1; p = e[p].nxt) {
        if (e[p].to == Fa[cur]) continue;

        pw[e[p].to] = e[p].w;
        peid[e[p].to] = p;
        epid[p] = e[p].to;

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
int tot;
void dfs2(int cur, int nowTop, std::vector<int> debug) {
    Top[cur] = nowTop;
    tot++;
    dnk[cur] = tot; rnk[tot] = cur;
    if (Son[cur] == -1) {
        for (auto u : debug) {
            printf("%d ", u);
        }
        puts("");
        return;
    }
    debug.push_back(Son[cur]);
    dfs2(Son[cur], nowTop, debug);
    for (int p = head[cur]; p != -1; p = e[p].nxt) {
        if (e[p].to == Fa[cur] || e[p].to == Son[cur]) continue;
        dfs2(e[p].to, e[p].to, std::vector<int>({e[p].to}));
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        init();
        scanf("%d", &n);
        for (int i = 0; i < n - 1; i++) {
            int x, y, w;
            scanf("%d%d%d", &x, &y, &w);
            insert(x, y, w);
        }
        dfs1(1, -1);
        tot = 0; dfs2(1, 1, std::vector<int>({1})); 
        
    }
}