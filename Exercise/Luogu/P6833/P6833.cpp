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

#define int long long

int n, m, a, b, c;
const int maxn = 1005;
int map[maxn][maxn];
int d[5][maxn][maxn];
int vis[maxn][maxn];
int cx[4] = {0, 1, 0, -1},
    cy[4] = {1, 0, -1, 0};
struct Node {
    int ux, uy, dis;
    bool operator < (Node b) const {
        return dis > b.dis;
    }
};
std::priority_queue<Node> q;

void dij(int px, int py, int id) {
    memset(vis, 0, sizeof(vis));
    memset(d[id], 31, sizeof(d[id]));
    d[id][px][py] = map[px][py];
    q.push({px, py, map[px][py]});
    while (!q.empty()) {
        Node p = q.top(); q.pop();
        int ux = p.ux, uy = p.uy;
        if (vis[ux][uy]) continue;
        vis[ux][uy] = true;
        for (int i = 0; i < 4; i++) {
            int qx = ux + cx[i], qy = uy + cy[i];
            if (qx < 1 || qy < 1 || qx > n || qy > m) continue;
            if (d[id][qx][qy] > d[id][ux][uy] + map[qx][qy]) {
                d[id][qx][qy] = d[id][ux][uy] + map[qx][qy];
                q.push({qx, qy, d[id][qx][qy]});
            }
        }
    }
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        // freopen(".out", "w", stdout);
    #endif
    
    read(n, m, a, b, c);

    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= m; j++) {
            read(map[i][j]);
        }
    }


    dij(n, a, 1);
    dij(1, b, 2);
    dij(1, c, 3);

    int ans = 1e18;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            ans = std::min(ans, d[1][i][j] + d[2][i][j] + d[3][i][j] - 2 * map[i][j]);
            // writeln(i, j, d[1][i][j], d[2][i][j], d[3][i][j], map[i][j], ans);
        }
    }
    writeln(ans);
    return 0;
}
