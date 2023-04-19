#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Edge {
    int from, to, next;
} e[2000005], eN[2000005];
int head[1000005], len, headN[1000005], lenN;
int dfn[1000005], low[1000005], ts, st[1000005], top;
bool vis[1000005];
int cnt, bel[1000005];
int col[1000005], colN[1000005];
int idg[1000005];
bool nvis[1000005];
void Insert(int u, int v) {
    e[++len].to = v;
    e[len].next = head[u];
    head[u] = len;
    e[len].from = u;
}
void InsertN(int u, int v) {
    eN[++lenN].to = v;
    eN[lenN].next = headN[u];
    headN[u] = lenN;
    eN[lenN].from = u;
}
bool Tarjan(int u) {
    dfn[u] = low[u] = ++ts;
    vis[u] = true;
    st[++top] = u;
    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].to;
        if (!dfn[v]) {
            if (!Tarjan(v)) return false;
            low[u] = min(low[u], low[v]);
        }
        else if (vis[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u]) {
        cnt++;
        int cl = -1;
        while (st[top + 1] != u) {
            if (~cl) {
                if (cl != col[st[top]]) {
                    return false;
                }
            }
            else {
                cl = col[st[top]];
            }
            int v = st[top--];
            bel[v] = cnt;
            vis[v] = false;
        }
        colN[cnt] = cl;
    }
    return true;
}
int Toposort() {
    queue<int> q;
    for (int i = 1; i <= cnt; i++) {
        if (!idg[i]) q.push(i);
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (colN[u] == 1) return u;
        for (int i = headN[u]; i; i = eN[i].next) {
            int v = eN[i].to;
            if (!(--idg[v])) q.push(v);
        }
    }
    return 0;
}
bool Dfs(int u) {
    bool fl = colN[u];
    nvis[u] = true;
    for (int i = headN[u]; i; i = eN[i].next) {
        int v = eN[i].to;
        if (!nvis[v]) fl &= Dfs(v);
    }
    return fl;
}
int n, m;
bool allWhite, blackToWhite, twoBlack;
void Solve() {
    scanf("%d%d", &n, &m);
    allWhite = true;
    blackToWhite = true;
    twoBlack = true;
    len = lenN = 0;
    memset(e, 0, sizeof(e));
    memset(eN, 0, sizeof(eN));
    memset(head, 0, sizeof(head));
    memset(headN, 0, sizeof(headN));
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    ts = top = 0;
    memset(vis, 0, sizeof(vis));
    memset(st, 0, sizeof(st));
    cnt = 0;
    memset(bel, 0, sizeof(bel));
    memset(col, 0, sizeof(col));
    memset(colN, 0, sizeof(colN));
    memset(idg, 0, sizeof(idg));
    memset(nvis, 0, sizeof(nvis));
    for (int i = 1; i <= n; i++) scanf("%d", &col[i]), allWhite &= !col[i], twoBlack &= col[i];
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        Insert(u, v);
    }
    if (allWhite) {
        putchar('B');
        return;
    }
    for (int i = 1; i <= n; i++) if (!dfn[i]) if (!Tarjan(i)) { putchar('N'); return; }
    for (int i = 1; i <= len; i++) {
        int u = e[i].from, v = e[i].to;
        if (bel[u] != bel[v]) {
            InsertN(bel[u], bel[v]);
            idg[bel[v]]++;
            blackToWhite &= (colN[bel[u]] == 1 && colN[bel[v]] == 0);
        }
    }
    if (Dfs(Toposort())) {
        bool fl = true;
        for (int i = 1; i <= cnt; i++) {
            if (colN[i] == 1 && !nvis[i]) {
                fl = false;
                break;
            }
        }
        if (fl) {
            putchar('A');
            return;
        }
    }
    if (cnt == 2) {
        if (blackToWhite || twoBlack) {
            putchar('B');
            return;
        }
    }
    putchar('N');
}
int T;
int main() {
    freopen("hack/5.in", "r", stdin);
    freopen("hack/5.out", "w", stdout);
    scanf("%d", &T);
    while (T--) Solve();
    return 0;
}