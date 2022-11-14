// Copyright 2022 Lotuses
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

#define gc getchar()
template<typename T>
void read(T &r) { // NOLINT
    r = 0; static char ch, last; // NOLINT
    ch = gc, last = 'z';
    while (ch < '0' || ch > '9') last = ch, ch = gc;
    while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
    r = (last == '-') ? -r : r;
}

template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) { // NOLINT
    read(arg);
    read(arg_left...);
}

#define maxn 114514
struct union_find_set { // 并查集模板
    #define min(x, y) (((x) < (y)) ? (x) : (y))
    int fa[maxn];
    void init(int n) {
        for (int i = 0; i <= min(maxn, n); i++) {
            fa[i] = i;
        }
    }
    int find(int x) {
        return fa[x] == x ? x : (fa[x] = find(fa[x]));
    }
    void uni(int x, int y) {
        fa[find(x)] = find(y);
    }
}ufs;

int n, m;
struct Edge {
    int from, to, cost, time, nxt;
};
std::vector<Edge> G[maxn];
std::vector<Edge> GG;
#define eps 1e-4
#define seps 1e-6

std::pair<double, int> ccph[maxn];

bool check(double cph) {
    for (int i = 0; i < m; i++) {
        ccph[i] = std::make_pair(GG[i].cost - cph * GG[i].time, i);
    }
    std::sort(ccph, ccph + m);
    ufs.init(n); int i = 0; double total = 0;
    for (i = 0; i < m && ccph[i].first <= seps; i++) {
        ufs.uni(GG[ccph[i].second].from, GG[ccph[i].second].to);
        total += ccph[i].first;
    }

    for (i; i < m; i++) {
        int fafrom = ufs.find(GG[ccph[i].second].from),
            fato   = ufs.find(GG[ccph[i].second].to);
        if (fafrom != fato) {
            total += ccph[i].first;
            ufs.uni(fafrom, fato);
        }
    }
    return total <= eps;
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    read(n, m);
    for (int i = 0; i < m; i++) {
        static int a, b, c, t;
        read(a, b, c, t);
        Edge e1 = {a, b, c, t, G[b].size()}, 
             e2 = {b, a, c, t, G[a].size()}; // 提前算好
        G[a].push_back(e1);
        G[b].push_back(e2);
        GG.push_back(e1);
    }

    double l = 0, r = 1e13;
    while (fabs(l - r) > eps) {
        double mid = (l + r) / 2;
        bool resu = check(mid);
        if (resu) {
            r = mid;
        } else {
            l = mid;
        }
        // printf("%.2lf", mid);
    }
    printf("%.3lf", l);
    return 0;
}
