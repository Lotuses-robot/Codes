// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
// #include <set>
// #include <list>
#include <queue>
// #include <stack>
// #include <string>
#include <algorithm>
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

#define int long long

const int maxn = 4e5 + 10;
int n, ix, c[maxn], ls[maxn], id[maxn];
struct Point {
    int l, r, id;
    bool operator < (const Point &y) const {
        return r > y.r;
    } 
} p[maxn];
std::priority_queue<Point> q;

bool check(int cap) {
    while (!q.empty()) q.pop();
    memcpy(ls, c, sizeof(int) * (n + 5));
    int idx = 1, cp;
    for (int i = 1; i <= n; i++) {
        if (!q.empty() && q.top().r < i) return 0;
        while (idx <= n && p[idx].l <= i) {
            q.push(p[idx++]);
        }
        cp = cap;
        while (cp && !q.empty()) {
            int dec = std::min(cp, ls[q.top().id]);
            cp -= dec;
            if (!(ls[q.top().id] -= dec)) q.pop();
        }
        while (!q.empty() && !ls[q.top().id]) q.pop();
    }
    return q.empty();
}

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n);
    for (int i = 1; i <= n; i++) {
        read(ls[i]);
        id[i] = i;
    }
    for (int i = 1; i <= n; i++) {
        read(ix);
        p[i].l = i - ix; p[i].r = i + ix;
    }

    std::sort(id + 1, id + n + 1, [](int x, int y) {
        return p[x].l < p[y].l;
    });
    for (int i = 1; i <= n; i++) {
        c[i] = ls[id[i]];
    }
    std::sort(p + 1, p + n + 1, [](Point x, Point y) {
        return x.l < y.l;
    });
    int idx = 0;
    std::for_each(p + 1, p + n + 1, [&idx](Point &x) {
        x.id = ++idx;
    });

    int l = 0, r = 1e9;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    writeln(r);
    return 0;
}