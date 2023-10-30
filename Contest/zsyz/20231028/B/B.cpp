// Copyright 2023 Lotuses
#define tsz signed
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
// #include <map>
// #include <set>
// #include <list>
// #include <queue>
// #include <stack>
// #include <string>
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
#define ins(a, b) (G[a].emplace_back(b))

#define ll long long

const int maxn = 1e4 + 10;

struct Point {
    int x, y;
} ty[maxn], esc[maxn];
struct Seg {
    int ix, iy;
    long double k, b;
    Seg(int x, int y): ix(x), iy(y) {
        if (ty[ix].x > ty[iy].x) std::swap(ix, iy);
        k = (double)(ty[ix].y - ty[iy].y) / (ty[ix].x - ty[iy].x);
        b = ty[ix].y - k * ty[ix].x;
    }
};
std::vector<Seg> segs;

ll d[maxn];
ll dis(Point a, Point b) {
    return 1ll * (a.x - b.x) * (a.x - b.x) + 1ll * (a.y - b.y) * (a.y - b.y);
}

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    // freopen("B.in", "r", stdin);
    // freopen("B.out", "w", stdout);

    int m, n;
    read(m, n);
    for (int i = 1; i <= m; i++) {
        read(ty[i].x, ty[i].y);
        if (i > 1) {
            segs.emplace_back(Seg(i, i - 1));
        }
    }
    long double k, b, x, y, ans; ll ansl;
    for (int i = 1; i <= n; i++) {
        read(esc[i].x, esc[i].y);
        ansl = 1e18;
        for (int j = 1; j <= m; j++) {
            ansl = std::min(ansl, dis(esc[i], ty[j]));
        }
        ans = ansl;
        for (auto e : segs) {
            k = -1 / e.k;
            b = esc[i].y - k * esc[i].x;
            x = - (b - e.b) / (k - e.k);
            // printf("%.4Lf\n", k);

            // double k0 = k;
            if (k == 0) {
                // writeln(ty[e.ix].x, esc[i].x);
                ans = std::min(ans, (long double)(ty[e.ix].x - esc[i].x) * (ty[e.ix].x - esc[i].x));
            } else if (std::isinf(k)) {
                ans = std::min(ans, (long double)(ty[e.ix].y - esc[i].y) * (ty[e.ix].y - esc[i].y));
            } else if (x >= ty[e.ix].x && x <= ty[e.iy].x) {
                y = k * x + b;
                ans = std::min(ans, (x - esc[i].x) * (x - esc[i].x) + (y - esc[i].y) * (y - esc[i].y));
            }
        }
        printf("%.4lf\n", sqrt(ans));
    }
    return 0;
}