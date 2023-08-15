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

const int maxn = 1e5 + 10;
int n, m;
int a[maxn];
struct Edge {
    int v, id;
};
std::vector<Edge> G[maxn];

int tstamp;
int dfn[maxn], low[maxn], id[maxn];
int st[maxn];
int ans = 0, stlen = 0;
std::vector<std::vector<int> > ssc;
void tarjan(int u, int bid) {
    dfn[u] = low[u] = ++tstamp;
    st[++stlen] = u;
    for (auto e : G[u]) {
        if (!dfn[e.v]) {
            tarjan(e.v, e.id);
            low[u] = std::min(low[u], low[e.v]);
        } else if (e.id != bid) {
            low[u] = std::min(low[u], dfn[e.v]);
        }
    }
    if (low[u] == dfn[u]) {
        ans++;
        int tmp = st[stlen--];
        static std::vector<int> qd; qd.clear();
        qd.push_back(tmp); id[tmp] = ssc.size();
        while (tmp != u) {
            tmp = st[stlen--];
            qd.push_back(tmp);
            id[tmp] = ssc.size();
        }
        ssc.push_back(qd);
    }
}

int an[maxn]; bool cnnt[maxn];
std::vector<int> Gn[maxn];

int dis[maxn], maxid = 1;
void dfs(int u, int fa) {
    // writeln(u, dis[u]);
    for (int v : Gn[u]) {
        if (v != fa) {
            dis[v] = dis[u] + an[v];
            if (dis[v] > dis[maxid]) {
                maxid = v;
            }
            dfs(v, u);
        }
    }
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, m);
    for (int i = 1; i <= n; i++) read(a[i]);
    for (int i = 1; i <= m; i++) {
        int u, v;
        read(u, v);
        G[u].push_back({v, i});
        G[v].push_back({u, i});
    }

    for (int i = 1; i <= n; i++) if (!dfn[i]) {
        tarjan(i, -1);
        while (stlen) stlen--;
    }

    // writeln(ssc.size());

    for (int i = 0; i < ssc.size(); i++) {
        for (int e : ssc[i]) {
            // write(e); putchar(' ');
            an[i] += a[e];
            for (auto e : G[e]) {
                if (!cnnt[id[e.v]] && id[e.v] != i) {
                    cnnt[id[e.v]] = true;
                    Gn[i].push_back(id[e.v]);
                }
            }
        }
        // puts("");
        for (int v : Gn[i]) {
            // writeln(i, v);
            cnnt[v] = false;
        }
        // puts("");
    }

    dis[1] = an[0];
    dfs(1, 0);
    memset(dis, 0, sizeof(dis));
    dis[maxid] = an[maxid];
    dfs(maxid, 0);
    writeln(dis[maxid]);
    return 0;
}
