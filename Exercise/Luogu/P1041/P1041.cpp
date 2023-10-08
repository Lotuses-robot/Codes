// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

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

int n, p, b[305][305], cnt[305], maxx, dis[305];
bool bol[305], vis[305];
std::vector<int> G[305], f[305];
struct node {
    int x, quan;
    node(int a, int b) : x(a), quan(b) {}
    friend bool operator<(node a, node b) { return a.quan > b.quan; }
};
int clean(int i) {
    bol[i] = true;
    int num = 1;
    int p = f[i].size();
    for (int j = 0; j < p; ++j) {
        num += clean(f[i][j]);
    }
    return num;
}
void reclean(int i) {
    bol[i] = false;
    int p = f[i].size();
    for (int j = 0; j < p; ++j) {
        reclean(f[i][j]);
    }
}
void dfs(int cen, int tot) {
    maxx = std::max(maxx, tot);
    for (int i = 0; i < cnt[cen]; ++i) {
        if (!bol[b[cen][i]]) {
            int num = clean(b[cen][i]);
            tot += num;
            dfs(cen + 1, tot);
            reclean(b[cen][i]);
            tot -= num;
        }
    }
}
void resolve(int i, int cen) {
    b[cen][cnt[cen]] = i;
    ++cnt[cen];
    int p = G[i].size();
    for (int j = 0; j < p; ++j) {
        if (dis[G[i][j]] == dis[i] + 1) {
            resolve(G[i][j], cen + 1);
            f[i].push_back(G[i][j]);
        }
    }
}
void solve() {
    std::priority_queue<node> que;
    for (int i = 0; i <= n; ++i)
        dis[i] = 999;
    dis[1] = 0;
    que.push(node(1, 0));
    while (!que.empty()) {
        node temp = que.top();
        que.pop();
        int x = temp.x;
        int p = G[x].size();
        for (int j = 0; j < p; ++j) {
            if (dis[G[x][j]] > dis[x] + 1) {
                dis[G[x][j]] = dis[x] + 1;
                que.push(node(G[x][j], dis[G[x][j]]));
            }
        }
    }
    resolve(1, 0);
}

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int x, y;

    read(n, p);
    for (int i = 0; i < p; ++i) {
        read(x, y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    solve();
    dfs(1, 0);
    writeln(n - maxx);
    return 0;
}