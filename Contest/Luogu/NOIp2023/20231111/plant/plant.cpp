// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <vector>
// #include <map>
// #include <set>
// #include <list>
#include <queue>
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

#define ll long long

const int maxn = 1e4 + 10, mod = 998244353;
int cnt[maxn];
std::vector<int> vis;
std::priority_queue<int, std::vector<int>, std::greater<int> > q[maxn];

tsz main() {
    freopen("plant.in", "r", stdin);
    freopen("plant.out", "w", stdout);
    
    int n, w, x;
    read(n, w);
    for (int i = 1; i <= n; i++) {
        read(x);
        for (int p = 2; p * p <= x; p++) {
            if (x % p == 0) vis.emplace_back(p);
            while (x % p == 0) cnt[p]++, x /= p;
        }
        if (x != 1) {
            vis.emplace_back(x);
            cnt[x]++;
        }
        for (int x : vis) { // vis_size: log x 
            q[x].push(cnt[x] + 1);
            cnt[x] = 0;
        }
        vis.clear();
    }
    for (int p = 2; p * p <= w; p++) { // O(log w * log (n log x + log w))
        while (w % p == 0) { // vis times: log w
            if (q[p].size() < n) q[p].push(2);
            else q[p].push(q[p].top() + 1), q[p].pop();
            w /= p;
        }
    }
    if (w != 1) {
        if (q[w].size() < n) q[w].push(2);
        else q[w].push(q[w].top() + 1), q[w].pop();
    }

    ll ans = 1;
    for (int i = 2; i < maxn; i++) { // all: (n log x + log w) -> z O(z log z)
        while (!q[i].empty()) ans = ans * q[i].top() % mod, q[i].pop();
    }
    writeln(ans);
    return 0;
}