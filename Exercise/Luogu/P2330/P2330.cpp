// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

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

const int maxn = 305;
struct Edge {
    int u, v, w;
    bool operator < (Edge b) const {
        return w < b.w;
    }
};
std::vector<Edge> G;
void ins(int u, int v, int w) {
    G.push_back({u, v, w});
}

int fa[maxn];
int find(int x) {
    if (fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}
int n, m;

bool check(int x) {
    for (int i = 1; i <= n; i++) fa[i] = i;
    int ans = 0;
    for (int i = 0; i < G.size() && G[i].w <= x; i++) {
        if (find(G[i].u) == find(G[i].v)) continue;
        fa[find(G[i].v)] = fa[find(G[i].u)];
        ans++;
    }
    // writeln(x, ans);
    return ans >= n - 1;
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, m);
    for (int i = 1; i <= m; i++) {
        static int x, y, z;
        read(x, y, z);
        ins(x, y, z);
    }
    std::sort(G.begin(), G.end());

    int l = 1, r = 1e5;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }

    if (check(l)) writeln(n - 1, l);
    else if (check(l + 1)) writeln(n - 1, l + 1);
    else writeln(n - 1, r);
    return 0;
}
