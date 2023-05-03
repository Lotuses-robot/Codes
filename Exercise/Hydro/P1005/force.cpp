#include <cstdio>
#include <cstring>

int n, m;
bool vis[1001][1001];

int cx[4] = {1, 0, -1, 0},
    cy[4] = {0, -1, 0, 1};

int dfs(int x, int y, int fac, int first = 0) {
    if (vis[x][y] || x < 1 || x > n || y < 1 || y > m) return 0;
    printf("%d %d\n", x, y);
    vis[x][y] = true;
    int ans = 1;
    ans += dfs(x + cx[fac], y + cy[fac], fac);
    if (!first) {
        fac++; if (fac > 3) fac -= 4;
        ans += dfs(x + cx[fac], y + cy[fac], fac);
    }
    vis[x][y] = false;
    return ans;
}

int main() {
    while (scanf("%d%d", &n, &m) == 2 && n && m) {
        memset(vis, 0, sizeof(vis));
        printf("%d\n", dfs(1, m, 0, 1));
    }
    return 0;
}