// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>

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

struct Node {
    int a, b;
    bool operator < (Node y) const {
        if (a != y.a) return a < y.a;
        return b >= y.b;
    }
} a[100005];

std::vector<int> ls;
std::map<int, int> mp;

struct Tree {
    struct Node {
        int l, r, lc, rc;
        int max;
    } tn[800006];
    int cnt;
    
    void init() {
        cnt = 0;
    }
    int ins(int l, int r) {
        int id = ++cnt;
        tn[id].l = l; tn[id].r = r;
        tn[id].lc = tn[id].rc = -1;
        tn[id].max = 0;
        return id;
    }
    void ch(int u, int x, int c) {
        if (tn[u].l == x && tn[u].r == x) {
            tn[u].max = c;
            return;
        }
        int mid = (tn[u].l + tn[u].r) >> 1;
        if (x <= mid) {
            if (tn[u].lc == -1) tn[u].lc = ins(tn[u].l, mid);
            ch(tn[u].lc, x, c);
        } else {
            if (tn[u].rc == -1) tn[u].rc = ins(mid + 1, tn[u].r);
            ch(tn[u].rc, x, c);
        }
        tn[u].max = std::max(tn[tn[u].lc].max, tn[tn[u].rc].max);
    }
    int query(int u, int l, int r) {
        if (tn[u].l == l && tn[u].r == r) {
            return tn[u].max;
        }
        int mid = (tn[u].l + tn[u].r) >> 1;
        if (r <= mid) {
            if (tn[u].lc == -1) return 0;
            return query(tn[u].lc, l, r);
        } else if (l > mid) {
            if (tn[u].rc == -1) return 0;
            return query(tn[u].rc, l, r);
        } else {
            int ansl, ansr;
            if (tn[u].lc == -1) ansl = 0;
            else ansl = query(tn[u].lc, l, mid);
            
            if (tn[u].rc == -1) ansr = 0;
            else ansr = query(tn[u].rc, mid + 1, r);
            return std::max(ansl, ansr);
        }
    }
} tr;

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i].a, a[i].b);
        ls.push_back(a[i].b);
    }
    std::sort(ls.begin(), ls.end());
    std::sort(a + 1, a + n + 1);
    int lcnt = 0;
    for (int i : ls) {
        if (mp[i] == 0) {
            mp[i] = ++lcnt;
        }
    }
    for (int i = 2; i <= n; i++) {
        if (a[i].a == a[i - 1].a) {
            a[i - 1].a = -1;
        }
    }
    int ans = 1;
    tr.init(); tr.ins(1, 1e5);
    if (a[1].a != -1) tr.ch(1, mp[a[1].b], 1);
    for (int i = 2; i <= n; i++) {
        if (a[i].a == -1) continue;
        int r = tr.query(1, 1, mp[a[i].b]);
        // writeln(r);
        ans = std::max(ans, i - r);
        tr.ch(1, mp[a[i].b], i);
    }
    writeln(ans);
    return 0;
}
