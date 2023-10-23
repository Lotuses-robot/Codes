// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <vector>
// #include <map>
// #include <set>
#include <stack>
// #include <queue>
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
#define ins(a, b) (G[a].push_back(b))

const int maxn = 5e5 + 10;
std::vector<int> G[maxn];
std::vector<int> ans[maxn];
int cnt = 0;
int dfn[maxn], low[maxn], idx = 0;
std::stack<int> st;

void tarjan(int u, int fa) {
    dfn[u] = low[u] = ++idx; st.push(u);
    int t = 0;
    for (int v : G[u]) {
        if (!dfn[v]) {
            t++;
            tarjan(v, u);
            low[u] = std::min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                cnt++;
                while (st.top() != v) ans[cnt].push_back(st.top()), st.pop();
                ans[cnt].push_back(st.top()); st.pop();
                ans[cnt].push_back(u);
            }
        } else if (v != fa) {
            low[u] = std::min(low[u], dfn[v]);
        }
    }
    if (fa == 0 && t == 0) { // self-loop
        ans[++cnt].push_back(u);
    }
}

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, m;
    read(n, m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        read(u, v);
        ins(u, v); ins(v, u);
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i, 0);
        }
    }
    writeln(cnt);
    for (int i = 1; i <= cnt; i++) {
        write(ans[i].size()); putchar(' ');
        for (int u : ans[i]) {
            write(u); putchar(' ');
        }
        puts("");
    }
    return 0;
}