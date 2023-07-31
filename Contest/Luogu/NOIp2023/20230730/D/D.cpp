// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
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

const int maxn = 4e5;
struct Edge {
    int v, w;
} G[maxn];
int inp[maxn];
int n, m;

int dfn[maxn], low[maxn], dfncnt, s[maxn], in_stack[maxn], tp;
int scc[maxn], sc;
int sz[maxn];
int pre[maxn];
bool dr[maxn];
int cr, ans = 0;

void init() {
    memset(G, 0, sizeof(G));
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(s, 0, sizeof(s));
    memset(in_stack, 0, sizeof(in_stack));
    memset(scc, 0, sizeof(scc));
    memset(sz, 0, sizeof(sz));
    memset(inp, 0, sizeof(inp));
    memset(pre, 0, sizeof(pre));
    memset(dr, 0, sizeof(dr));
    tp = sc = ans = cr = 0;
}

void tarjan(int u) {
    low[u] = dfn[u] = ++dfncnt, s[++tp] = u, in_stack[u] = 1;
    int v = G[u].v;
    if (scc[v] != 0) return;
    if (!dfn[v]) {
        tarjan(v);
        low[u] = std::min(low[u], low[v]);
    } else if (in_stack[v]) {
        low[u] = std::min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        ++sc;
        while (s[tp] != u) {
            scc[s[tp]] = sc;
            sz[sc]++;
            in_stack[s[tp]] = 0;
            --tp;
        }
        scc[s[tp]] = sc;
        sz[sc]++;
        in_stack[s[tp]] = 0;
        --tp;
    }
}

int bg;
void dfs(int u, int e) {
    if (sz[scc[u]] > 1) {
        pre[u] = e;
        return;
    }
    if (e + G[u].w > m) {
        ans++;
        dfs(G[u].v, 0);
    } else {
        dfs(G[u].v, e + G[u].w);
    }
}

int calc(int brk) {
    int ans = 1;
    dr[brk] = true;
    for (int i = G[brk].v; i != brk; i = G[i].v) dr[i] = false;

    for (int bq = G[brk].v; bq != brk; bq = G[bq].v) {
        int nc = pre[bq];
        for (int u = bq; u != brk; u = G[u].v) {
            nc += G[u].w;
            if (nc > m || dr[u] == true) ans += (!dr[u]), nc = 0, dr[u] = true;
        }
    }
    return ans;
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        // freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        init();
        read(n, m);
        for (int i = 1; i <= n; i++) {
            read(G[i].v, G[i].w);
            inp[G[i].v]++;
        }
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) tarjan(i);
        }
        for (int i = 1; i <= n; i++) {
            if (inp[i] == 0) {
                dfs(i, 0);
            }
        }

        for (int qq = 1; qq <= sc; qq++) {
            if (sz[qq] > 1) {
                cr = qq;
                for (int i = 1; i <= n; i++)
                    if (scc[i] == cr) {
                        bg = i;
                    }
                int i = bg, cnt = 0, anss = 998244353;
                
                puts("?");
                anss = std::min(anss, calc(i));
                for (i = G[bg].v; i != bg; i = G[i].v) {
                    anss = std::min(anss, calc(i));
                }
                ans += anss;
            }
        }
        writeln(ans);

    }
    return 0;
}
