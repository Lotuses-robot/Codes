#include <cstdio>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        static int p[100];
        int n, ans = 0;
        scanf("%d", &n);

        for (int i = 0; i < n; i++) {
            scanf("%d", &p[i]);
        }

        for (int i = n - 2; i >= 0; i--) {
            while (p[i] >= p[i + 1] && p[i]) {
                p[i] >>= 1;
                ans++;
            }
            if (p[i + 1] == 0 && p[i] == 0) {
                ans = -1;
                break;
            }
        }

        printf("%d\n", ans);
    }
    return 0;
}