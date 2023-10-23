// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>
// #include <map>
// #include <set>
// #include <list>
#include <queue>
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

const int maxn = 1e4 + 10;
int a[maxn];
int n, m;
std::vector<int> G[maxn];

std::stack<int> st;
int dfn[maxn], low[maxn], id[maxn], cnt, idx;
bool ins[maxn];
std::vector<int> ans[maxn];
void tarjan(int u) {
    dfn[u] = low[u] = ++idx; st.push(u); ins[u] = true;
    for (int v : G[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = std::min(low[u], low[v]);
        } else if (ins[v]) {
            low[u] = std::min(low[u], dfn[v]);
        }
    }
    if (low[u] >= dfn[u]) {
        ans[++cnt].push_back(st.top());
        id[st.top()] = cnt; ins[st.top()] = false;
        while (st.top() != u) {
            st.pop();
            ans[cnt].emplace_back(st.top());
            id[st.top()] = cnt; ins[st.top()] = false;
        }
        st.pop();
    }
}

#define insn(a, b) (Gn[a].emplace_back(b))
std::vector<int> Gn[maxn];
bool vis[maxn]; int in[maxn];
int na[maxn];
int f[maxn], maxa = 0;

std::queue<int> q;
void bfs() {
    for (int i = 1; i <= cnt; i++) {
        if (!in[i]) q.push(i);
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        f[u] += na[u];
        maxa = std::max(maxa, f[u]);
        for (int v : Gn[u]) {
            f[v] = std::max(f[u], f[v]);
            in[v]--;
            if (!in[v]) {
                q.push(v);
            }
        }
    }

}

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, m);
    for (int i = 1; i <= n; i++) read(a[i]);
    for (int i = 1; i <= m; i++) {
        int u, v;
        read(u, v);
        ins(u, v);
    }
    for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i);
    for (int i = 1; i <= cnt; i++) {
        for (int j : ans[i]) {
            na[i] += a[j];
            for (int v : G[j]) {
                if (id[v] != i && !vis[id[v]]) {
                    insn(i, id[v]);
                    vis[id[v]] = true;
                }
            }
        }
        for (int v : Gn[i]) {
            in[v]++;
            vis[v] = false;
        }
    }
    bfs();
    writeln(maxa);
    return 0;
}