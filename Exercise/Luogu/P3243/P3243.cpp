// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <queue>
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

const int maxn = 1e5 + 5;
int n, m;
std::vector<int> G[maxn];
bool vis[maxn];
int in[maxn];
std::vector<int> ans;
int fa[maxn];

int find(int x) {
    if (x == fa[x]) return x;
    return fa[x] = find(fa[x]);
}

void init() {
    memset(vis, 0, sizeof(vis));
    memset(in, 0, sizeof(in));
    for (int i = 1; i <= n; i++) {
        G[i].clear();
        fa[i] = i;
    }
    ans.clear();
}

std::priority_queue<int, std::vector<int>, std::greater<> > q;
void find() {
    for (int i = 1; i <= n; i++) {
        if (!in[i]) q.push(i);
    }

    while (!q.empty()) {
        int u = q.top(); q.pop();
        ans.push_back(u);
        for (int e : G[u]) {
            in[e]--;
            if (!in[e]) {
                q.push(e);
            }
        }
    }
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        read(n, m);
        init();
        bool flag = false;
        for (int i = 1; i <= m; i++) {
            static int u, v;
            read(u, v);
            G[u].push_back(v);
            in[v]++;
            // fa[find(u)] = fa[find(v)];
            // vis[v] = true; vis[u] = true;
            if (u == v) flag = true;
        }
        if (flag) {
            puts("Impossible!");
            continue;
        }
        // for (int i = 2; i <= n; i++) {
        //     if (find(i) != find(i - 1)) {
        //         G[i - 1].push_back(i);
        //         in[i]++;
        //         fa[find(i)] = fa[find(i - 1)];
        //         writeln(i - 1, i);
        //     }
        // }
        find();
        if (ans.size() != n) {
            puts("Impossible!");
            continue;
        }
        for (int i = 0; i < ans.size(); i++) {
            write(ans[i]); putchar(' ');
        }
        puts("");
    }
    return 0;
}
