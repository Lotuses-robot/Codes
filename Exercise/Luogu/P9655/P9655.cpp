// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <stack>
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
#define debug(arg, args...) { printf("db <%d> ", __LINE__); writeln(arg, ##args); }
#else
#define debug(arg, args...) {}
#endif

const int maxn = 5e5 + 10;
char ch[maxn];
std::vector<int> G[maxn];
int upd[maxn];
std::stack<int> st;

int siz[maxn], son[maxn], dep[maxn], last[maxn], fa[maxn];
void dfs1(int u, int f) {
    if (ch[u] == '(') st.push(u), last[u] = u;
    else {
        if (st.empty()) upd[u] = -1;
        else upd[u] = st.top(), st.pop();
    }

    son[u] = -1; siz[u] = 1; fa[u] = f;
    for (int v : G[u]) {
        if (v == fa[u]) continue;
        dep[v] = dep[u] + 1;
        dfs1(v, u);
        siz[u] += siz[v];
        if (son[u] == -1 || siz[v] > siz[son[u]]) son[u] = v;
    }

    if (ch[u] == '(') st.pop();
    else if (upd[u] != -1) st.push(upd[u]);
}

int top[maxn];
void dfs2(int u, int tp) {
    top[u] = tp;
    if (son[u] == -1) return;
    dfs2(son[u], tp);
    for (int v : G[u]) {
        if (v != fa[u] && v != son[u]) {
            dfs2(v, v);
        }
    }
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] > dep[top[v]])
            u = fa[top[u]];
        else
            v = fa[top[v]];
    }
    return dep[u] > dep[v] ? v : u;
}

int dis(int u, int v) {
    return dep[u] + dep[v] - 2 * dep[lca(u, v)];
}

int sizz[maxn];
void dsiz(int u) {
    if (upd[u] != -1 && upd[u] != u) {
        // writeln(u, upd[u]);
        sizz[upd[u]] += dis(last[upd[u]], u);
        last[upd[u]] = u;
    }
    for (int v : G[u]) {
        if (v != fa[u]) {
            dsiz(v);
        }
    }
}

int f[maxn];
void dp(int u) {
    for (int v : G[u]) {
        if (v != fa[u]) dp(v);
    }
    if (ch[u] == '(') {
        int up = upd[fa[u]];
        if (up > 0) f[up] += f[u];
    }
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n;
    read(n);
    scanf("%s", ch + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        read(u, v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    memset(upd, -1, sizeof(upd));
    memset(last, -1, sizeof(last));
    dfs1(1, 1);
    dfs2(1, 1);
    dsiz(1);
    for (int i = 1; i <= n; i++) {
        if (last[i] != -1 && last[i] != i) {
            // writeln(last[i]);
            // writeln(i, upd[last[i]], last[i]);
            sizz[upd[last[i]]] += dis(upd[last[i]], last[i]);
            sizz[upd[last[i]]] /= 2;
            sizz[upd[last[i]]]++;
            f[upd[last[i]]] = sizz[upd[last[i]]];
            // writeln(i, sizz[i]);
        }
    }
    dp(1);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = std::max(ans, f[i]);
    }
    writeln(ans);
    return 0;
}