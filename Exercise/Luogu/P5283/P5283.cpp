// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <queue>
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

#define int long long

const int maxn = 2e6 + 10, maxt = 2e7 + 10;
int a[maxn];
struct Tree {
    struct Node {
        int ch[2], cnt;
    } nd[maxt];
    int cnt;

    int c() {
        int id = ++cnt;
        nd[id].ch[0] = nd[id].ch[2] = 0;
        nd[id].cnt = 0;
        return id;
    }

    void init() {
        cnt = 0;
        c();
    }

    void add(int x) {
        int u = 1;
        nd[u].cnt++;
        for (int i = 31; i >= 0; i--) {
            int mv = (x >> i) & 1;
            if (!nd[u].ch[mv]) {
                nd[u].ch[mv] = c();
            }
            u = nd[u].ch[mv];
            nd[u].cnt++;
        }
    }

    int query(int x, int rk) {
        int u = 1;
        for (int i = 31; i >= 0; i--) {
            int mv = (x >> i) & 1;
            if (rk <= nd[nd[u].ch[mv ^ 1]].cnt) {
                x |= 1ll << i;
                u = nd[u].ch[mv ^ 1];
            } else {
                if (mv) x ^= 1ll << i;
                rk -= nd[nd[u].ch[mv ^ 1]].cnt;
                u = nd[u].ch[mv];
            }
        }
        return x;
    }
} t;

struct Point {
    int w, id, rk;
    bool operator < (Point b) const {
        return w < b.w;
    }
};
std::priority_queue<Point> q;

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    t.init();
    int n, k, ans = 0;
    read(n, k);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
        a[i] ^= a[i - 1];
        t.add(a[i]);
    }
    t.add(a[0]);
    for (int i = 0; i <= n; i++) {
        // writeln(t.query(a[i], 1));
        q.push({t.query(a[i], 1), i, 1});
    }
    for (int i = 1; i <= k << 1; i++) {
        auto p = q.top(); q.pop();
        ans += p.w;
        if (p.rk < n) q.push({t.query(a[p.id], p.rk + 1), p.id, p.rk + 1});
    }
    writeln(ans >> 1);
    return 0;
}