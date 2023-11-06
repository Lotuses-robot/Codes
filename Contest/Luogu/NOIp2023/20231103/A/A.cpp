// Copyright 2023 Lotuses
#define tsz signed
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

#define int long long

const int maxn = 1e6 + 10;
int mod;

int qpow(int x, int y) {
    int ans = 1;
    do {
        if (y & 1) ans = ans * x % mod;
        x = x * x % mod;
    } while (y >>= 1);
    return ans;
}

int fac1[maxn], fac2[maxn];

struct Tree {
    struct Node {
        int l, r, lc, rc, val;
    } nd[maxn << 2];
    int cnt;

    void init() { cnt = 0; }

    int bt(int l, int r) {
        int u = ++cnt;
        nd[u] = { l, r, -1, -1, 1 };
        if (l == r) {
            nd[u].val = l % mod;
        } else {
            int mid = (l + r) >> 1;
            nd[u].lc = bt(l, mid);
            nd[u].rc = bt(mid + 1, r);
            nd[u].val = nd[nd[u].lc].val * nd[nd[u].rc].val % mod;
        }
        return u;
    }
    
    int query(int u, int l, int r) const {
        if (nd[u].l == l && nd[u].r == r) {
            return nd[u].val;
        } else {
            int mid = (nd[u].l + nd[u].r) >> 1;
            if (r <= mid) return query(nd[u].lc, l, r);
            else if (l > mid) return query(nd[u].rc, l, r);
            else return query(nd[u].lc, l, mid) * query(nd[u].rc, mid + 1, r) % mod;
        }
    }
} tr;

void init(int n) {
    fac1[0] = fac2[n + 1] = 1;
    for (int i = 1; i <= n; i++) {
        fac1[i] = fac1[i - 1] * qpow(i, i - 1) % mod;
    }
    for (int i = n; i >= 1; i--) {
        fac2[i] = fac2[i + 1] * qpow(i, n - i + 1) % mod;
    }
    tr.init(); tr.bt(1, n);
}

tsz main() {
    #ifdef LOCAL
        freopen("data/ex_a3.in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    int T;
    read(T);
    while (T--) {
        int n, q;
        read(n, mod, q);
        init(n);
        while (q--) {
            int r, ans = 1;
            read(r);
            if (r == 0 || r == n) {
                ans = 1 % mod;
            } else if (r < n - r) {
                ans = fac1[r] * fac2[n - r + 1] % mod;
                ans = ans * qpow(tr.query(1, r + 1, n - r), r) % mod;
            } else if (r == n - r) {
                ans = fac1[r] * fac2[n - r + 1] % mod;
            } else {
                ans = fac1[n - r] * fac2[r + 1] % mod;
                ans = ans * qpow(tr.query(1, n - r + 1, r), n - r) % mod;
            }
            writeln(ans);
        }
    }
    return 0;
}