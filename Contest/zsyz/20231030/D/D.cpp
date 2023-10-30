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

const int maxn = 1e5 + 10;
int n;
char ch[maxn];
std::vector<int> G[maxn];
bool vis[maxn];

int rt, alsz;
int siz[maxn], wei[maxn];
void getrt(int u, int fa) {
    siz[u] = 1;
    wei[u] = 0;
    for (int v : G[u]) {
        if (vis[v] || v == fa) continue;
        getrt(v, u);
        siz[u] += siz[v];
        wei[u] = std::max(wei[u], siz[v]);
    }
    wei[u] = std::max(wei[u], alsz - siz[u]);
    if (!rt || wei[rt] > wei[u]) {
        rt = u;
    }
}
int getsz(int u, int fa) {
    int ans = 1;
    for (int v : G[u]) {
        if (vis[v] || v == fa) continue;
        ans += getsz(v, u);
    }
    return ans;
}

auto add(int u, std::pair<int, int> p) {
    switch (ch[u]) {
        case 'a': p.first++; break;
        case 'b': p.second++; break;
        case 'c': p.first--; p.second--; break;
    }
    return p;
}
std::map<std::pair<int, int>, int> mp;

void dfs(int u, int fa, std::pair<int, int> d) {
    // writeln(u, d.first, d.seecond);
    mp[d]++;
    for (int v : G[u]) {
        if (vis[v] || v == fa) continue;
        dfs(v, u, add(v, d));
    }
}

int calc(int u, std::pair<int, int> bg = {0, 0}, int f = -1) {
    if (f == -1) f = u;
    mp.clear();
    // mp[{0, 0}] = 1;
    dfs(u, u, bg);
    // puts("");
    int ans = 0;
    for (auto p : mp) {
        // writeln(p.first.first, p.first.second, p.second);
        auto d = add(f, p.first);
        ans += p.second * mp[{-d.first, -d.second}];
        mp[{-d.first, -d.second}] = 0;
    }
    return ans;
}

int dfz(int u) {
    vis[u] = true;
    int ans = calc(u);
    // writeln(u, ans);
    // puts("");
    for (int v : G[u]) {
        if (vis[v]) continue;
        ans -= calc(v, add(v, {0, 0}), u);
        alsz = getsz(v, v);
        rt = 0; getrt(v, v);
        ans += dfz(rt);
    }
    return ans;
}

tsz main() {
   #ifdef LOCAL
       freopen(".in", "r", stdin);
       freopen(".out", "w", stdout);
   #endif
    
    read(n);
    scanf("%s", ch + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        read(u, v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    alsz = getsz(1, 1);
    rt = 0; getrt(1, 1);
    writeln(dfz(rt));
    return 0;
}
