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

// #define __DEBUG
#ifdef __DEBUG
#define debug(arg, args...) { printf("db <%d> ", __LINE__); writeln(arg, ##args); }
#else
#define debug(arg, args...) {}
#endif

const int N = 2e5 + 10;

struct Edge {
    int u, v;
};

int n, m;
std::vector<Edge> G[N];
bool st[N];
int mi[N];
bool vis[N];
std::vector<int> q, nq;

bool check(int k) {
    memset(mi, 0, sizeof(mi));
    memset(vis, 0, sizeof(vis));
    q.clear(); nq.clear();
    for (int i = 1; i <= n; i++) {
        if (G[i].size() < k) {
            q.push_back(i);
        }
    }
    int cnt = n;
    while (true) {
        nq.clear();
        nq = q;
        q.clear();
        for (int i : nq) {
            // write(i); putchar(' ');
            if (vis[i]) continue;
            vis[i] = true;
            cnt--;
            for (auto e : G[i]) {
                mi[e.v]++;
                if (G[e.v].size() - mi[e.v] < k && !vis[e.v]) q.push_back(e.v);
            }
        }
        // puts("");
        if (!q.empty()) {
            continue;
        }
        return cnt >= 1;
    }
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    read(n, m);
    for (int i = 0; i < m; i++) {
        int u, v;
        read(u, v);
        G[u].push_back({u, v});
        G[v].push_back({v, u});
    }
    int l = 0, r = n - 1;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (check(mid)) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    writeln(l);
    return 0;
}