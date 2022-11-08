#include <cstdio>

char ch[2145][2145];
int f[2145][2145];

#define max(a, b) ((a) > (b) ? (a) : (b))

int main() {
    freopen("lamp.in", "r", stdin);
    freopen("lamp.out", "w", stdout);
    int n, m, ans = 0, tot, tot2 = 0;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", ch[i]);
    }

    for (int i = 0; i < n; i++) {
        tot = tot2 = 0;
        for (int j = 0; j <= m; j++) {
            if (ch[i][j] == '#' || j == m) {
                ans = max(tot + tot2 - 1, ans);
                tot = 0; tot2 = 0;
            } else {
                if (!f[i][j]) {
                    int temp = 0;
                    for (int x = i; x < n; x++) {
                        if (ch[x][j] == '#') {
                            break;
                        } else {
                            temp++;
                        }
                    }
                    for (int x = i; x < n; x++) {
                        if (ch[x][j] != '#') {
                            f[x][j] = temp;
                        }
                    }
                }
                tot = max(f[i][j], tot);
                tot2++;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}