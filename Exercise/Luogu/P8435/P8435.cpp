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
std::vector<std::vector<int> > ans;
int n, m;
std::vector<int> G[maxn];
int dfn[maxn], low[maxn], cnt = 0; bool in_st[maxn];
std::stack<int> st;

void tarjan(int u, int fa) {
    dfn[u] = low[u] = ++cnt;
    st.push(u);
    int cc = 0;
    for (int v : G[u]) {
        if (!dfn[v]) {
            cc++;
            tarjan(v, u);
            low[u] = std::min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                // writeln(u, v);
                std::vector<int> subt; subt.clear();
                while (st.top() != v) subt.push_back(st.top()), st.pop();
                st.pop(); subt.push_back(v);
                subt.push_back(u);
                ans.push_back(subt);
            }
        } else if (v != fa) {
            low[u] = std::min(low[u], dfn[v]);
        }
        // while (st.top() != u) st.pop();
    }
    if (fa == 0 && cc == 0) {
        ans.push_back({u});
    }
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        read(u, v);
        G[u].push_back(v);
        G[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        if (dfn[i]) continue;
        while (!st.empty()) st.pop();
        tarjan(i, 0);
    }

    writeln(ans.size());
    for (auto e : ans) {
        write(e.size()); putchar(' ');
        for (int v : e) {
            write(v); putchar(' ');
        }
        puts("");
    }
    return 0;
}
