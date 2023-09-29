// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/assoc_container.hpp>

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
#define debug(arg, args...) { printf("d <%d> ", __LINE__); writeln(arg, ##args); }
#else
#define debug(arg, args...) {}
#endif

#define int long long

const int maxn = 1e5 + 10;
int fa[maxn], cost[maxn], lead[maxn];
std::vector<int> G[maxn];
int rt;
__gnu_pbds::priority_queue<int, std::less<int>, __gnu_pbds::binomial_heap_tag> pq[maxn];
int pts[maxn];
int n, m;
long long ans = 0;

void dfs(int u) {
    pts[u] = 0;
    for (int v : G[u]) {
        dfs(v);
        pts[u] += pts[v];
        pq[u].join(pq[v]);
    }
    pq[u].push(cost[u]);
    pts[u] += cost[u];
    while (pts[u] > m) {
        pts[u] -= pq[u].top();
        pq[u].pop();
    }
    ans = std::max(ans, (long long)(lead[u] * pq[u].size()));
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, m);
    for (int i = 1; i <= n; i++) {
        read(fa[i], cost[i], lead[i]);
        if (fa[i] != 0) G[fa[i]].push_back(i);
        else rt = i;
    }

    dfs(rt);
    writeln(ans);
    return 0;
}
