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

// #define __DEBUG
#ifdef __DEBUG
#define debug(arg, args...) { printf("db <%d> ", __LINE__); writeln(arg, ##args); }
#else
#define debug(arg, args...) {}
#endif

const int maxn = 1e5 + 10;
struct Tree {
    struct Node {
        int l, r, lc, rc;
        double max_; int ans;
    } nd[maxn << 2];
    int cnt;

    int bt(int l, int r) {
        int id = ++cnt;
        Node &d = nd[id];
        d.l = l; d.r = r;
        d.max_ = d.ans = 0;
        if (l != r) {
            int mid = (l + r) >> 1;
            d.lc = bt(l, mid);
            d.rc = bt(mid + 1, r);
        }
        return id;
    }

    int getans(int u, double h) {
        Node &d = nd[u];
        if (d.l == d.r) {
            return d.max_ > h ? 1 : 0;
        }
        Node &lc = nd[d.lc], &rc = nd[d.rc];
        if (lc.max_ > h) {
            return getans(d.lc, h) + d.ans - lc.ans;
        } else {
            return getans(d.rc, h);
        }
    }

    void change(int u, int x, double c) {
        Node &d = nd[u];
        if (d.l == d.r) {
            d.max_ = c;
            d.ans = 1;
        } else {
            int mid = (d.l + d.r) >> 1;
            if (x <= mid) {
                change(d.lc, x, c);
            } else {
                change(d.rc, x, c);
            }
            Node &lc = nd[d.lc], &rc = nd[d.rc];
            d.max_ = std::max(lc.max_, rc.max_);
            d.ans = lc.ans + getans(d.rc, lc.max_);
        }
    }
} tr;

#define int long long

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        int n, m;
        read(n, m);
        if (n == m) {
            writeln(0);
        } else if ((n & m) == n || (n & m) == m) {
            writeln(1);
        } else {
            writeln(2);
        }
    }
    return 0;
}
