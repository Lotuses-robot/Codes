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

int n, k;
int lowbit(int x) { return x & (-x); }
const int mod = 998244353;

namespace sub1 {
    const int maxn = 20;
    std::vector<int> v;
    int a[maxn], p[maxn];

    void init() {
        for (int i = 1; i <= 10; i++) {
            p[i] = std::__lg(lowbit(i)) + 1;
        }
    }

    int calc() {
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            ans += i * (n - i + 1) * p[a[i]];
        }
        return ans;
    }

    void solve() {
        v.clear();
        int cnt = 1;
        for (int i = 1; i <= n; i++) {
            cnt *= i;
            a[i] = i;
        }
        for (int i = 1; i <= cnt; i++) {
            std::next_permutation(a + 1, a + n + 1);
            v.emplace_back(calc());
        }
        std::sort(v.begin(), v.end());
        // for (int x : v) {
        //     writeln(x);
        // }
        writeln(v[k - 1]);
    }
}

namespace sub2 {
    std::vector<int> v1, v2;
    void solve() {
        v1.clear();
        v2.clear();
        for (int i = 1; i <= n; i++) {
            v1.emplace_back(i * (n - i + 1));
        }
        for (int i = 1; i <= n; i++) {
            v2.emplace_back(std::__lg(lowbit(i)) + 1);
        }
        std::sort(v1.begin(), v1.end());
        std::sort(v2.begin(), v2.end());
        std::reverse(v1.begin(), v1.end());
        int ans = 0;
        for (int i = 0; i < n; i++) {
            // writeln(v1[i], v2[i]);
            ans += 1ll * v1[i] * v2[i] % mod;
            ans %= mod;
        }
        writeln(ans);
    }
}

tsz main() {
    freopen("npc.in", "r", stdin);
    freopen("npc.out", "w", stdout);

    sub1::init();

    int T;
    read(T);
    while (T--) {
        read(n, k);
        if (n <= 10) {
            sub1::solve();
        } else {
            sub2::solve();
        }
    }
}