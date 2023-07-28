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

#define int long long

const int maxn = 1e7 + 5;
int fa[maxn];
int find(int u) {
    if (fa[u] == u) return u;
    return fa[u] = find(fa[u]);
}
void uni(int u, int v) {
    fa[find(u)] = fa[find(v)];
}

struct Edge {
    int u, v, w;
    bool operator < (const Edge b) const {
        return w > b.w;
    }
};
std::vector<Edge> g;

int block[maxn];

signed main() {
    #ifdef LOCAL
        // freopen(".in", "r", stdin);
        // freopen(".out", "w", stdout);
    #endif
    
    memset(block, -1, sizeof(block));

    int n, k, x, y, w;
    read(n, k);
    for (int i = 1; i <= k; i++) {
        read(x);
        block[x] = x;
    }
    int al = 0;
    for (int i = 1; i < n; i++) {
        fa[i] = i;
        read(x, y, w); al += w;
        g.push_back({x, y, w});
    }
    fa[n] = n;
    std::sort(g.begin(), g.end());
    
    int ans = 0;
    for (auto e : g) {
        if (block[find(e.u)] == -1 || block[find(e.v)] == -1) {
            if (block[find(e.u)] != -1) {
                int tp = block[find(e.u)];
                uni(e.u, e.v);
                block[find(e.u)] = tp;
            } else if (block[find(e.v)] != -1) {
                int tp = block[find(e.v)];
                uni(e.u, e.v);
                block[find(e.v)] = tp;
            } else {
                uni(e.u, e.v);
            }
            ans += e.w;
        }
        // writeln(ans);
    }

    writeln(al - ans);
    return 0;
}
