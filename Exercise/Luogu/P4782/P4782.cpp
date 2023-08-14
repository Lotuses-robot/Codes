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

const int maxn = 2e6 + 5;
std::vector<int> G[maxn];

int dfn[maxn], low[maxn], ins[maxn];
std::vector<int> ssc[maxn]; int cnt = 0, scnt = 0;
int id[maxn];
std::stack<int> st;

void tarjan(int u) {
    low[u] = dfn[u] = ++cnt;
    ins[u] = true; st.push(u);
    for (int v : G[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = std::min(low[u], low[v]);
        } else if (ins[v]) {
            low[u] = std::min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        scnt++;
        while (st.top() != u) {
            id[st.top()] = scnt;
            ins[st.top()] = false;
            ssc[scnt].push_back(u);
            st.pop();
        }
        id[st.top()] = scnt;
        ins[st.top()] = false;
        ssc[scnt].push_back(u);
        st.pop();
    }
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, m;
    read(n, m);
    for (int i = 1; i <= m; i++) {
        int x, a, y, b;
        read(x, a, y, b);
        G[x + a * n].push_back(y + (b ^ 1) * n);
        G[y + b * n].push_back(x + (a ^ 1) * n);
    }

    for (int i = 1; i <= 2 * n; i++) if (!dfn[i]) tarjan(i);

    for (int i = 1; i <= n; i++) {
        if (id[i] == id[i + n]) {
            puts("IMPOSSIBLE");
            return 0;
        }
    }

    puts("POSSIBLE");

    for (int i = 1; i <= n; i++) {
        write(id[i] < id[i + n]); putchar(' ');
    }
    puts("");
    return 0;
}
