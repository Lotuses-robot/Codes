// Copyright 2023 Lotuses
#define tsz signed
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
// #include <map>
// #include <set>
// #include <queue>
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
#define ins(a, b) (G[a].pushback(b))

#define int long long

const int maxn = 5e5 + 20, mod = 998244353;
const double eps = 1e-7;
int n, sum, q, tot, sxor;
int id[maxn], f[maxn], finv[maxn];
struct Point {
    int l, r;
    int bcs, id;
} qry[maxn << 1];

int C(int n, int m) { 
    return f[n] * finv[m] % mod * finv[n - m] % mod;
}

int qow(int x, int y) {
    int ans = 1;
    do {
        if (y & 1) ans *= x, ans %= mod; x *= x, x %= mod;
    } while (y >>= 1);
    return ans;
}

int inv(int x) {
    return qow(x, mod - 2);
}

void init() {
    f[0] = 1;
    finv[0] = 1;
    for (int i = 1; i <= n + 10; i++) {
        f[i] = f[i - 1] * i % mod;
        finv[i] = inv(f[i]);
    }
}

int a[maxn], b[maxn], col[maxn], cnt[maxn];
void inita() {
    std::sort(b + 1, b + n + 1);
    sum = sqrt(n) + eps;
    for (int i = 1; i <= n; i++) a[i] = std::lower_bound(b + 1, b + n + 1, a[i]) - b;
    for (int i = 1; i <= n; i++) cnt[a[i]]++;
    for (int i = 1; i <= n; i++) {
        if (cnt[i] >= sum) {
            id[i] = ++tot;
        }
    }
}

int cnt1[maxn], cnt2[maxn], ans[maxn];
void ch(int x, int k) {
    if (id[x]) {
        sxor ^= cnt2[id[x]];
        cnt2[id[x]] += k;
        sxor ^= cnt2[id[x]];
    } else {
        cnt1[col[x]]--; sxor ^= col[x];
        col[x] += k;
        cnt1[col[x]]++; sxor ^= col[x];
    }
}

int getans() {
    int ans = 0;
    for (int i = 1; i < sum; i++) {
        if (i >= (sxor ^ i)) {
            ans += C(i, sxor ^ i) * cnt1[i] % mod;
        }
    }
    ans %= mod;
    for (int i = 1; i <= tot; i++) {
        if (cnt2[i] >= (sxor ^ cnt2[i])) {
            ans += C(cnt2[i], sxor ^ cnt2[i]);
        }
    }
    ans %= mod;
    return ans;
}

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, q);
    init();
    for (int i = 1; i <= n; i++) {
        read(a[i]);
        b[i] = a[i];
    }
    inita();
    for (int i = 1; i <= q; i++) {
        read(qry[i].l, qry[i].r);
        qry[i].id = i;
        qry[i].bcs = (qry[i].l - 1) / sum;
    }

    std::sort(qry + 1, qry + q + 1, [] (Point a, Point b) {
        if (a.bcs != b.bcs) return a.bcs < b.bcs;
        if (a.bcs & 1) return a.r > b.r;
        return a.r < b.r;
    });

    int l = 1, r = 1;
    ch(a[1], 1);
    for (int i = 1; i <= q; i++) {
        int tl = qry[i].l, tr = qry[i].r;

        while (l > tl) ch(a[--l], 1);
        while (r < tr) ch(a[++r], 1);
        while (l < tl) ch(a[l++], -1);
        while (r > tr) ch(a[r--], -1);

        if (sxor) ans[qry[i].id] = getans();
        else ans[qry[i].id] = 0;
    }
    for (int i = 1; i <= q; i++){
        writeln(ans[i]);
    }
    return 0;
}