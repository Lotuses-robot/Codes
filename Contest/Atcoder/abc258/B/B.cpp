#include <cstdio>
#include <vector>

int n;
int a[100][100];
const int
direc[8][2] = {
    {1, 0},
    {0, 1},
    {-1 ,0},
    {0, -1},
    {1, 1},
    {1, -1},
    {-1, 1},
    {-1, -1}
};

int get(int &x, int &y, int dir) {
    x += direc[dir][0], y += direc[dir][1];

    if (x <= 0) {
        x += n;
    } else if (x > n) {
        x -= n;
    }
    if (y <= 0) {
        y += n;
    } else if (y > n) {
        y -= n;
    }
}

#define max(a, b) ((a) > (b) ? (a) : (b))
bool vis[100][100];
int dfs(int x, int y, int nowans, int tot) {
    if (tot >= 8) {
        return nowans;
    }
    int maxn = -1;
    for (int i = 0; i < 8; i++) {
        int px = x, py = y;
        get(px, py, i);
        if (vis[px][py]) {
            continue;
        }
        vis[px][py] = true;
        maxn = max(maxn, dfs(px, py, nowans + a[px][py], tot + 1));
        vis[px][py] = false;
    }
    return ans;
}

int main() {
    static char chr[20];
    static std::vector<std::pair<int, int> > v;
    int maxn = -1;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", chr + 1);
        for (int j = 1; j <= n; j++) {
            a[i][j] = chr[j] - '0';
            if (a[i][j] > maxn) {
                v.clear();
                v.push_back(std::make_pair(i, j));
                maxn = a[i][j];
            } else if (a[i][j] == maxn) {
                v.push_back(std::make_pair(i, j));
            }
        }
    }
}