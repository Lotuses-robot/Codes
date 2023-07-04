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

#define int long long

// #define __DEBUG
#ifdef __DEBUG
#define debug(arg, args...) { printf("db <%d> ", __LINE__); writeln(arg, ##args); }
#else
#define debug(arg, args...) {}
#endif

struct Edge {
    int u, v, w;
};
std::vector<Edge> G[200005];

void insert(int u, int v, int w) {
    G[u].push_back({u, v, w});
    G[v].push_back({v, u, w});
}

struct Trie {
    struct Node {
        bool v;
        int s[2];
    };
    Node nd[5000006];
    int cnt;

    void init() {
        cnt = 1;
    }

    int cv[40];
    void convert(int k) {
        int i = 31;
        while (i >= 1) {
            cv[i] = k & 1;
            k >>= 1;
            i--;
        }
    }
    void insert(int k) {
        convert(k);
        int cur = 1;
        for (int i = 1; i <= 31; i++) {
            if (nd[cur].s[cv[i]]) {
                cur = nd[cur].s[cv[i]];
            } else {
                nd[cur].s[cv[i]] = ++cnt;
                cur = cnt;
            }
        }
        nd[cur].v = true;
    }
    int query(int k) {
        convert(k);
        int cur = 1, cp = 1, ans = 0;
        for (int i = 1; i <= 31; i++) {
            if (nd[cp].s[cv[i] ^ 1]) {
                cp = nd[cp].s[cv[i] ^ 1];
                ans++;
            } else {
                cp = nd[cp].s[cv[i]];
            }
            cur = nd[cur].s[cv[i]];
            ans <<= 1; // 这里爆了 int 所以开了 ll 不过改不改无所谓反正过了
        }
        return ans >> 1;
    }
} tr;

int xoor[200005];

void dfs(int u, int xr, int fa) {
    tr.insert(xr);
    xoor[u] = xr;
    for (auto e : G[u]) {
        if (e.v != fa) {
            dfs(e.v, xr ^ e.w, u);
        }
    }
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n;
    read(n);
    for (int i = 1; i < n; i++) {
        static int u, v, w;
        read(u, v, w);
        insert(u, v, w);
    }
    tr.init();
    dfs(1, 0, -1);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = std::max(ans, tr.query(xoor[i]));
    }
    writeln(ans);
    return 0;
}
