#include <cstdio>

int d[114514];

int main() {
    freopen("card.in", "r", stdin);
    freopen("card.out", "w", stdout);
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        d[l - 1]++; d[r]--;
    }

    int now = 0, tot = 0;
    for (int i = 1; i <= n; i++) {
        now += d[i - 1];
        if (now == m) {
            tot++;
        }
    }
    printf("%d\n", tot);
    return 0;
}