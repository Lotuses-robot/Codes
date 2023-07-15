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

#define __DEBUG
#ifdef __DEBUG
#define debug(arg, args...) { printf("db <%d> ", __LINE__); writeln(arg, ##args); }
#else
#define debug(arg, args...) {}
#endif

const int maxn = 200004;
struct Edge {
    int u, v;
}; std::vector<Edge> G[maxn];
int n, k;

int fa[maxn], h[maxn], s[maxn], hs[maxn];
void dfs1(int u) {
    int hsp = -1, mx = -1;
    for (Edge e : G[u]) {
        if (e.v != fa[u]) {
            fa[e.v] = u;
            h[e.v] = h[u] + 1;
            dfs1(e.v);
            s[u] += s[e.v];
            if (s[e.v] > mx) {
                mx = s[e.v];
                hsp = e.v;
            }
        }
    }
    s[u]++;
    hs[u] = hsp;
}

int top[maxn], dfn[maxn], r[maxn], cnt = 0;
void dfs2(int u, int tp) {
    top[u] = tp;
    dfn[u] = ++cnt;
    r[cnt] = u;
    if (hs[u] > 0) dfs2(hs[u], tp);
    for (Edge e : G[u]) {
        if (e.v != fa[u] && e.v != hs[u]) {
            dfs2(e.v, e.v);
        }
    }
}

void insert(int u, int v) {
    G[u].push_back({u, v});
    G[v].push_back({v, u});
}

struct fw {
    int arr[maxn * 4];
    int lowbit(int x) {
        return x & (-x);
    }
    void add(int x, int a) {
        while (x <= n) {
            arr[x] += a;
            x += lowbit(x);
        }
    }
    int query(int x) {
        int ans = 0;
        while (x > 0) {
            ans += arr[x];
            x -= lowbit(x);
        }
        return ans;
    }
} fenw;

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, k);
    
    for (int i = 1; i < n; i++) {
        int u, v;
        read(u, v);
        insert(u, v);
    }


    fa[1] = -1;
    dfs1(1);
    dfs2(1, 1);
    // puts("fk");


    for (int i = 1; i <= k; i++) {
        // if (i % 1000 == 0) writeln(i);
        int x, y;
        read(x, y);
        // debug(i);
        while (top[x] != top[y]) { // 必须判断是不是同链
            if (h[top[x]] < h[top[y]]) std::swap(x, y); // 向上跳之后判断高度差
            fenw.add(dfn[top[x]], 1);
            fenw.add(dfn[x] + 1, -1);
            x = fa[top[x]];
            if (x == -1) x = 1; // 如果跳到根节点马上跳回来占位置
        }
        if (h[x] < h[y]) std::swap(x, y);
        fenw.add(dfn[y], 1);
        fenw.add(dfn[x] + 1, -1); // 信仰之跃
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = std::max(ans, fenw.query(dfn[i]));
        // writeln(fenw.query(dfn[i]));
    }
    writeln(ans);
    return 0;
}
