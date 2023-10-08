// Copyright 2023 Lotuses
#define tsz signed
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

const int maxn = 1e5 + 10;
std::vector<int> G[maxn];
int dfn[maxn], low[maxn], ins[maxn], idx = 0;
std::stack<int> st;
int nid[maxn], ids = 0;
std::vector<int> ssc[maxn], ng[maxn];

void tarjan(int u) {
    // writeln(u);
    dfn[u] = low[u] = ++idx;
    ins[u] = 1; st.push(u);
    for (int v : G[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = std::min(low[u], low[v]);
        } else if (ins[v]) {
            low[u] = std::min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        ids++;
        while (st.top() != u) {
            nid[st.top()] = ids;
            ssc[ids].push_back(st.top());
            ins[st.top()] = 0;
            st.pop();
        }
        nid[st.top()] = ids;
        ssc[ids].push_back(st.top());
        ins[st.top()] = 0;
        st.pop();
    }
}

int out[maxn];
bool cnn[maxn];

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        // freopen(".out", "w", stdout);
    #endif
    
    int n, m;
    read(n, m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        read(u, v);
        G[u].push_back(v);
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) tarjan(i);
    }
    for (int i = 1; i <= ids; i++) {
        for (int u : ssc[i]) {
            for (int v : G[u]) {
                if (nid[v] != nid[u] && !cnn[nid[v]]) {
                    cnn[nid[v]] = true;
                    ng[nid[u]].push_back(nid[v]);
                    out[nid[u]]++;
                }
            }
        }
        for (int v : ng[i]) {
            cnn[v] = false;
        }
    }
    int id = 0, cnt = 0;
    for (int i = 1; i <= ids; i++) {
        if (out[i] == 0) {
            cnt++;
            id = i;
        }
    }
    if (cnt > 1) puts("0");
    else writeln(ssc[id].size());
    return 0;
}