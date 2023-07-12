// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <stack>
#include <queue>
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

const int maxn = 1005;
int n, m;
int w[maxn], v[maxn], d[maxn];
int f[maxn][maxn];
struct Edge {
    int u, v;
}; std::vector<Edge> G[maxn];

void insert(int u, int v) {
    G[u].push_back({u, v});
}

int id[maxn], ct = 0;
int dfn[maxn], low[maxn], cnt = 0;
bool ins[maxn];
std::stack<int> st;
void tarjan(int u) {
    dfn[u] = low[u] = ++cnt; ins[u] = true;
    st.push(u);
    for (auto e : G[u]) {
        if (!dfn[e.v]) {
            tarjan(e.v);
            low[u] = std::min(low[u], low[e.v]);
        } else if (ins[e.v]) {
            low[u] = std::min(low[u], dfn[e.v]);
        }
    }
    if (dfn[u] == low[u]) {
        ct++;
        while (st.top() != u) {
            id[st.top()] = ct;
            ins[st.top()] = false;
            st.pop();
        }
        id[st.top()] = ct;
        ins[st.top()] = false;
        st.pop();
    }
}

int Nw[maxn], Nv[maxn];
bool vis[maxn][maxn];
int in[maxn];
std::vector<Edge> Gn[maxn];

std::queue<int> q;
void sort() {
    memset(f, -63, sizeof(f));
    for (int i = 1; i <= ct; i++) {
        if (!in[i]) q.push(i);
        f[i][0] = 0;
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int j = m; j >= Nv[u]; j--) {
            f[u][j] = f[u][j - Nv[u]] + Nw[u];
        }
        for (int j = Nv[u] - 1; j >= 1; j--) {
            f[u][j] = -998244353;
        }
        for (auto e : Gn[u]) {
            for (int j = m; j >= 0; j--) {
                for (int k = 0; k <= j; k++) {
                    f[e.v][j] = std::max(f[e.v][j], f[e.v][j - k] + f[u][k]);
                }
            }
            in[e.v]--;
            if (!in[e.v]) {
                q.push(e.v);
            }
        }
    }
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, m);
    for (int i = 1; i <= n; i++) read(v[i]);
    for (int i = 1; i <= n; i++) read(w[i]);
    for (int i = 1; i <= n; i++) {
        read(d[i]);
        insert(i, d[i]);
    }

    for (int i = 0; i <= n; i++) if (!dfn[i]) tarjan(i);

    for (int i = 0; i <= n; i++) {
        Nw[id[i]] += w[i];
        Nv[id[i]] += v[i];
        bool flag = 0;
        for (auto e : G[i]) {
            if (id[i] != id[e.v] && !vis[id[i]][id[e.v]]) {
                Gn[id[i]].push_back({id[i], id[e.v]});
                vis[id[i]][id[e.v]] = true;
                in[id[e.v]]++;
                flag |= true;
            }
        }
        if (!flag && !vis[id[i]][id[0]]){
            Gn[id[i]].push_back({id[i], id[0]});
            vis[id[i]][id[0]] = true;
            in[id[0]]++;
        }
    }
    sort();
    int ans = 0;
    for (int q = 0; q <= 0; q++)
    for (int i = Nv[id[q]]; i <= m; i++) {
        ans = std::max(ans, f[id[q]][i]);
    }
    writeln(ans);
    return 0;
}
