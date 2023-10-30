// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <set>
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

const int maxn = 1e5 + 10;
int n, a[maxn], f[maxn], fx[maxn];
std::vector<int> G[maxn];
std::map<int, int> g[maxn], ls;
int pt[maxn], ct = 0, calc = 0;

void dfs(int u, int fa) {
    if (G[u].size() == 1 && u != fa) {
        f[u] = 0;
        g[++ct][a[u]] = 1;
        fx[u] = 0;
        pt[u] = ct;
    } else {
        for (int v : G[u]) {
            if (v != fa) dfs(v, u);
        }
        ls.clear();
        int maxid = -1, cnt = 0;
        for (int v : G[u]) {
            if (v == fa) continue;
            f[u] += f[v]; cnt++;
            if (maxid == -1) maxid = v;
            else if (g[pt[maxid]].size() < g[pt[v]].size()) {
                maxid = v;
            }
        }
        fx[u] = fx[maxid] ^ a[u];
        ls = g[pt[maxid]]; pt[u] = pt[maxid]; int pmax = 1;
        for (int v : G[u]) {
            if (v == fa || v == maxid) continue;
            for (auto p : g[pt[v]]) {
                int now = ls[p.first] += p.second;
                calc++;
                if (calc % 1000 == 0) writeln(calc);
                if (pmax < now) {
                    pmax = now;
                    g[pt[u]].clear();
                    g[pt[u]][p.first ^ fx[v] ^ fx[maxid]] = 1;
                } else if (pmax == now) {
                    g[pt[u]][p.first ^ fx[v] ^ fx[maxid]] = 1;
                }
                // writeln(p.first, p.second);
            }
        }
        // writeln(cnt, pmax);
        f[u] += cnt - pmax;
    }
}

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        // freopen(".out", "w", stdout);
    #endif
    
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        read(u, v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1, 1);
    writeln(f[1] + (!g[1][fx[1]]));
    return 0;
}