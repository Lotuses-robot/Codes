// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
// #include <set>
// #include <list>
// #include <queue>
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

#define int unsigned long long

#define ll long long

const int maxn = 5e5 + 10;
int n, m, q;
int fa[maxn], a[maxn];
std::vector<int> G[maxn];
struct Hash {
    int sum, x;

    Hash() { }
    Hash(int x): x(x) { sum = 0; }
    Hash(int sum, int x): sum(sum), x(x) {}

    void add(int a) {
        sum = (sum * x + a);
    }

    bool operator == (const Hash &b) const {
        return sum == b.sum;
    }

    bool operator < (const Hash &b) const {
        return sum < b.sum;
    }

    Hash operator + (const Hash &b) const {
        return { (sum + b.sum), x };
    }
    Hash operator - (const Hash &b) const {
        return { (sum - b.sum), x };
    }
} s[maxn], as[maxn];

struct Point {
    Hash key;
    int val;
    bool operator < (const Point &b) {
        return key < b.key;
    }
}; std::vector<Point> mp;

void dfs(int u) {
    int cnt = 0;
    for (int v : G[u]) {
        cnt++;
        s[v] = s[u];
        s[v].add(cnt);
        mp.push_back({s[v], v});
        dfs(v);
    }
}

struct Ta {
    Hash c[maxn << 2];
    int n;

    int lowbit(int x) const {
        return x & (-x);
    }

    void add(int x, Hash k) {
        while (x <= n) {
            c[x] = c[x] + k;
            x += lowbit(x);
        }
    }

    Hash query(int x) const {
        Hash ans(500009);
        while (x > 0) {
            ans = ans + c[x];
            x -= lowbit(x);
        }
        return ans;
    }

    Hash query(int l, int r) const {
        return query(r) - query(l - 1);
    }
} t;

int invf[maxn], fac[maxn];

int qpow(int x, int y) {
    int ans = 1;
    do {
        if (y & 1) ans = ans * x;
        x = x * x;
    } while (y >>= 1);
    return ans;
}

int inv(int x) {
    return qpow(x, -1);
}

Hash hsh;

int check(int u, int l, int r) {
    hsh = t.query(l, r);
    // writeln(hsh.sum);
    hsh.sum = hsh.sum * invf[m - r];
    // writeln(hsh.sum);
    hsh.sum = hsh.sum + s[u].sum * fac[r - l + 1];
    // writeln(u, l, r, hsh.sum);
    // writeln(mp.find(hsh) != mp.end() ? 0 : -1);
    
    auto p = std::lower_bound(mp.begin(), mp.end(), (Point){hsh, 0});
    if (p == mp.end() || !(p->key == hsh)) return 0;
    return p -> val;
}

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, m, q);

    for (int i = 1; i <= n; i++) {
        read(fa[i]);
        G[fa[i]].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        std::sort(G[i].begin(), G[i].end());
    }
    for (int i = 1; i <= m; i++) {
        read(a[i]);
    }

    s[0] = Hash(500009);
    dfs(0);
    std::sort(mp.begin(), mp.end());

    t.n = m + 10;

    // writeln(qpow(10, -1));

    as[m + 1] = Hash(500009);
    int f = 1, cnt = 0;
    fac[cnt] = invf[cnt] = f;
    for (int i = m; i >= 1; i--) {
        as[i] = as[m + 1];
        as[i].sum = f * a[i];
        t.add(i, as[i]);
        f = f * as[i].x;
        fac[++cnt] = f; invf[cnt] = inv(f);
        // writeln(invf[cnt]);
    }

    int op, x, y, z;
    for (int i = 1; i <= q; i++) {
        read(op, x, y);
        if (op == 1) {
            read(z);
            int l = y, r = z, ans;
            while (l < r) {
                int mid = (l + r + 1) >> 1;
                if (check(x, y, mid)) {
                    l = mid;
                } else {
                    r = mid - 1;
                }
                // writeln(l, r);
            }
            
            ans = check(x, y, l);
            if (!ans) writeln(x);
            else writeln(ans);
        } else {
            as[x].sum = -as[x].sum;
            t.add(x, as[x]);
            as[x].sum = fac[m - x] * y;
            t.add(x, as[x]);
        }
    }
    return 0;
}