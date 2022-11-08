#include <cstdio>
#include <queue>
#include <cstring>

#define maxn 200005
int row[3][maxn];
bool vis[3][maxn];
std::deque<int> dq[3];
#define max(x, y) ((x) > (y) ? (x) : (y))
#define min(x, y) ((x) < (y) ? (x) : (y))

int n;

int getAns(int x, int y, int nowTime) {
    while (!dq[x].empty() && dq[x].front() <= y) dq[x].pop_front();
    auto p = dq[x].begin();
    // for (p = dq[x].begin(); p != dq[x].end() - 1; ++p) {
    //     if (row[x][*p] != row[x][*(p + 1)]) {
    //         break;
    //     }
    // }
    int maxx1 = *p;
    int ano = (x == 2 ? 1 : 2);
    while (!dq[ano].empty() && dq[ano].front() <= y) dq[ano].pop_front();
    int maxx2 = dq[ano].front();
    nowTime = max(nowTime + n - (y == 0 ? 1 : y), row[x][maxx1] + (n - maxx1 + 1));

    printf("getAns2: %d\n", nowTime);
    nowTime = max(nowTime + n - y, row[ano][maxx2] + (maxx2 - x + 1));
    
    printf("getAns2: %d\n", nowTime);

    return nowTime;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        memset(vis, 0, sizeof(vis));
        scanf("%d", &n);
        while (!dq[1].empty()) dq[1].pop_front();
        for (int i = 1; i <= n; i++) {
            scanf("%d", &row[1][i]);
            while (!dq[1].empty() && row[1][dq[1].back()] < row[1][i]) dq[1].pop_back();
            dq[1].push_back(i);
        }
        while (!dq[2].empty()) dq[2].pop_front();
        for (int i = 1; i <= n; i++) {
            scanf("%d", &row[2][i]);
            while (!dq[2].empty() && row[2][dq[2].back()] < row[2][i]) dq[2].pop_back();
            dq[2].push_back(i);
        }
        int x = 1, y = 1, nowTM = 0, ans = 1145141919;
        ans = min(ans, getAns(1, 0, nowTM));
        while (y <= n) {
            printf("%d\n", nowTM);
            vis[x][y] = true;
            if (vis[(x == 2 ? 1 : 2)][y] && x != n) {
                ans = min(ans, getAns(x, y, nowTM));
            }
            if (x == 1) {
                if (!vis[2][y]) { // down
                    nowTM = max(nowTM, row[2][y]) + 1;
                    x = 2;
                } else if (y < n) { // right
                    nowTM = max(nowTM, row[1][y + 1]) + 1;
                    y++;
                }
            } else {
                if (!vis[1][y]) { // up
                    nowTM = max(nowTM, row[1][y]) + 1;
                    x = 1;
                } else if (y < n) { // right
                    nowTM = max(nowTM, row[2][y + 1]) + 1;
                    y++;
                }
            }
            if (y == n && vis[(x == 2 ? 1 : 2)][y]) {
                ans = min(nowTM, ans);
                break;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}