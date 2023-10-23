// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
// #include <map>
// #include <set>
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
std::vector<std::pair<int, int> > G[maxn];
int dfn[maxn], low[maxn], cnt, idx;
std::vector<int> ans[maxn];
std::stack<int> st;

void tarjan(int u, int fd) {
    dfn[u] = low[u] = ++idx; st.push(u);
    for (auto [v, id] : G[u]) {
        if (!dfn[v]) {
            tarjan(v, id);
            low[u] = std::min(low[u], low[v]);
        } else if (id != fd) {
            low[u] = std::min(low[u], dfn[v]);
        }
    }
    if (low[u] >= dfn[u]) {
        ans[++cnt].push_back(st.top());
        while (st.top() != u) {
            st.pop();
            ans[cnt].push_back(st.top());
        }
        st.pop();
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
        ins(u, std::make_pair(v, i)); ins(v, std::make_pair(u, i));
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i, 0);
        }
    }

    writeln(cnt);
    for (int i = 1; i <= cnt; i++) {
        write(ans[i].size()); putchar(' ');
        for (int j : ans[i]) {
            write(j); putchar(' ');
        }
        puts("");
    }
    return 0;
}