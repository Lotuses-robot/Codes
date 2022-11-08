#include <cstdio>

int main() {
    static int map[10][10];
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= 2; i++) {
        for (int j = 1; j <= 2; j++)
            scanf("%d", &map[i][j]);
    }

    printf("%d\n", map[n][m]);
}