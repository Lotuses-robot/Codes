#include <cstdio>
#include <cstring>
#define int long long
#define ll long long

int mx[4] = {1, 0, -1, 0},
    my[4] = {0, 1, 0, -1};
char ch[1145104];
ll map[2001][2001];
int lst[2001][2001];

signed main() {
    memset(lst, 0, sizeof(lst));
    memset(map, 0, sizeof(map));
    int n, m, x, y;
    scanf("%lld%lld%lld%lld", &n, &m, &x, &y);
    scanf("%s", ch);

    lst[x][y] = 1;
    for (int i = 1; i <= m; i++) {
        int p;
        switch (ch[i - 1]) {
            case 'N': p = 1; break;
            case 'S': p = 3; break;
            case 'W': p = 2; break;
            case 'E': p = 0; break;
        }
        x += mx[p]; y += my[p];
        // printf("%lld %lld\n", x, y);
        map[x][y] += 1ll * (1 + (i - lst[x][y])) * (i - lst[x][y]) / 2;
        lst[x][y] = i + 1;
    }
    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= n; y++) {
            map[x][y] += 1ll * (1 + (m - lst[x][y])) * (m - lst[x][y]) / 2;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf(j != n ? "%lld " : "%lld", map[j][n - i + 1]);
        }
        if (i != n) puts("");
    }
    return 0;
}