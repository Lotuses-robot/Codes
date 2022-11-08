#include <cstdio>
#include <cstring>

int p[514][514];
int yy[514][514];
char ch[514];

int minx, maxx, miny, maxy;

void init() {
    minx = miny = 1145141919;
    maxx = maxy = -1145141919;
}

int cx[4] = {1, 0, -1, 0},
    cy[4] = {0, 1, 0, -1};

void update(int x, int y) {
    if (x < minx) minx = x;
    if (x > maxx) maxx = x;
    if (y < miny) miny = y;
    if (y > maxy) maxy = y;
}
int n, m;

void dfs(int x, int y) {
    update(x, y);
    for (int ci = 0; ci < 4; ci++) {
        int ccx = x + cx[ci], ccy = y + cy[ci];
        if (0 <= ccx && ccx < n && 0 <= ccy && ccy < m && p[ccx][ccy]) {
            p[ccx][ccy] = 0;
            dfs(ccx, ccy);
        }
    }
}

int main() {
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) {
            scanf("%s", ch);
            for (int j = 0; j < m; j++) {
                p[i][j] = ch[j] - '0';
            }
        }
        memcpy(yy, p, sizeof(p));
        bool flag = true;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (p[i][j]) {
                    init();
                    p[i][j] = 0;
                    dfs(i, j);

                    flag = true;
                    for (int x = minx; x <= maxx; x++) {
                        for (int y = miny; y <= maxy; y++) {
                            flag &= yy[x][y];
                        }
                    }
                }
                if (!flag) break;
            }
            if (!flag) break;
        }
        if (!flag) {
            puts("NO");
        } else {
            puts("YES");
        }
    }
    return 0;
}