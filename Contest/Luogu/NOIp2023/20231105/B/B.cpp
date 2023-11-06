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
#include <bitset>
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

const int maxn = 3e3 + 10;
int c[maxn], n;
std::vector<int> G[maxn];

namespace sub1 {
    std::bitset<30> b;
    int cnt[30]; bool vis[30];

    void dfs(int u, int fa) {
        cnt[c[u]]++; vis[u] = true;
        for (int v : G[u]) {
            if (v == fa) continue;
            if (b.test(v)) {
                dfs(v, u);
            }
        }
    }
    
    int check() {
        int sum = 0;
        std::for_each(cnt + 1, cnt + n + 1, [&sum] (int x) { sum += x; });
        for (int i = 1; i <= n; i++) {
            if ((cnt[i] << 1) > sum) {
                return 1;
            }
        }
        return 0;
    }

    void solve() {
        int ans = 0;
        for (int a = 0; a < (1 << n); a++) {
            b = a << 1;
            bool flag = false, fail = false;
            memset(cnt, 0, sizeof(cnt));
            memset(vis, 0, sizeof(vis));
            // writeln(a);
            for (int i = 1; i <= n; i++) {
                if (b.test(i) && !flag) {
                    dfs(i, i);
                    flag = true;
                } else if (b.test(i) && flag && !vis[i]) {
                    fail = true;
                    break;
                }
            }
            if (fail) continue;
            ans += check();
        }
        writeln(ans);
    }
}

namespace sub2 {
    int cnt[maxn];

    void solve() {
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            memset(cnt, 0, sizeof(cnt));
            int maxx = 0;
            for (int j = i; j <= n; j++) {
                maxx = std::max(maxx, ++cnt[c[j]]);
                if ((maxx << 1) > (j - i + 1)) {
                    ans++;
                }
            }
        }
        writeln(ans);
    }
}

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n);
    for (int i = 1; i <= n; i++) {
        read(c[i]);
    }
    for (int i = 1; i < n; i++) {
        static int x, y;
        read(x, y);
        ins(x, y);
        ins(y, x);
    }
    if (n <= 20) {
        sub1::solve();
    } else {
        sub2::solve();
    }
    return 0;
}