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

typedef long long ll;
const int maxn = 2e5 + 10;
int n, k;
int a[maxn];
ll sum[maxn], s[maxn];

int lowbit(int x) { return x & (-x); }
struct ta {
    ll c[maxn];
    void add(int x, ll y) {
        while (x <= n + 2) {
            c[x] = std::max(c[x], y);
            x += lowbit(x);
        }
    }
    ll query(int x) {
        ll ans = -0x3f3f3f3f3f3f3f3f;
        while (x > 0) {
            ans = std::max(c[x], ans);
            x -= lowbit(x);
        }
        return ans;
    }
} f;

bool check(ll c) {
    memset(f.c, -63, sizeof(ll) * (n + 5));
    int ans = 0, ret, pos;
    pos = std::lower_bound(s + 1, s + n + 3, 0) - s;
    pos = n + 2 - pos + 1;
    f.add(pos, 0);
    for (int i = 1; i <= n; i++) {
        pos = std::lower_bound(s + 1, s + n + 3, sum[i] - c) - s; pos = n + 2 - pos + 1;
        ret = f.query(pos) + 1;
        ans = std::max(ret, ans);
        pos = std::lower_bound(s + 1, s + n + 3, sum[i]) - s; pos = n + 2 - pos + 1;
        f.add(pos, ret);
    }
    return ans >= k;
}

tsz main() {
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
    int T;
    read(T);
    while (T--) {
        read(n, k);
        for (int i = 1; i <= n; i++) {
            read(a[i]);
            sum[i] = sum[i - 1] + a[i];
            s[i] = sum[i];
            // writeln(-1, i, sum[i]);
        }
        s[n + 1] = 0; s[n + 2] = 1e18;
        std::sort(s + 1, s + n + 3);
        ll l = -1e15, r = 1e15;
        while (l < r) { 
            ll mid = (l + r) >> 1;
            // writeln(l, r, mid);
            if (check(mid)) { // lower
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        writeln(r);
    }
    return 0;
}