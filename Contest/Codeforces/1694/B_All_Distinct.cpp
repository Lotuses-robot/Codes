#include <cstdio>
#include <cstring>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        static int a[1000001];
        memset(a, 0, sizeof(a));
        int n, tot1 = 0, tot2 = 0, q;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &q);
            a[q]++;
        }
        for (int i = 1; i <= 10000; i++) {
            if (a[i] != 0 && a[i] % 2 == 0) {
                a[i] = 2;
            } else {
                a[i] %= 2;
            }
            if (a[i] == 1) {
                tot1++;
            } else if (a[i] == 2) {
                tot2++;
            }
        }
        if (tot2 % 2 != 0) tot2--;
        printf("%d\n", tot1 + tot2);
    }
    return 0;
}