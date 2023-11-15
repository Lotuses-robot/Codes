// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
// #include <set>
// #include <list>
// #include <queue>
// #include <stack>
// #include <string>
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

#define ll long long
const int maxn = 1e5 + 10;
int n, m;
int a[maxn], to[maxn], id[maxn];
std::vector<int> G[maxn];
bool mp[30][30];

int dfn[maxn], cnt = 0;
void dfs(int u) {
    dfn[u] = ++cnt;
    for (int v : G[u]) dfs(v);
}

#define max(a, b) ((a) > (b) ? (a) : (b))

ll ans = 0;
ll f[maxn][30];
ll d[30];
void dp(int u) {
    if (G[u].empty()) {
        f[u][id[u]] = a[u];
        return;
    }
    f[u][0] = a[u];
    for (int v : G[u]) {
        if (mp[to[u]][to[v]]) continue;
        dp(v);
        for (int i = 0; i <= m; i++) d[i] = f[u][i];
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= m; j++) {
                if (!mp[i][to[v]]) {
                    d[j] = max(d[j], f[u][i] + f[v][j]);
                }
            }
        }
        for (int i = 0; i <= m; i++) {
            f[u][i] = d[i];
            ans = max(ans, d[i]);
        }
    }
}

tsz main() {
    // #ifdef LOCAL
    //     freopen("data/C3.in", "r", stdin);
    //     freopen(".out", "w", stdout);
    // #endif
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);

    read(n, m);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    for (int i = 1; i <= n; i++) {
        int sz, v;
        read(sz);
        for (int j = 1; j <= sz; j++) {
            read(v);
            G[i].emplace_back(v);
        }
    }
    memset(f, -63, sizeof(f));
    dfs(1);
    for (int i = 1; i <= m; i++) {
        int u, v;
        read(u, v);
        if (dfn[u] >= dfn[v]) std::swap(u, v);
        if (!to[u]) to[u] = i;
        if (!to[v]) to[v] = i;
        id[u] = to[u];
        mp[to[u]][to[v]] = true;
    }

    dp(1);
    writeln(ans);
    return 0;
}
