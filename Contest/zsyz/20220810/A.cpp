#include <cstdio>

int main() {
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        if (n % 3 == 0) {
            int now = 1;
            for (int i = 0; i < n / 3 * 2; i++, now ^= 1) {
                printf("%d", now + 1);
            }
        } else if (n % 3 == 1) {
            int now = 0;
            for (int i = 0; i < n / 3 * 2 + 1; i++, now ^= 1) {
                printf("%d", now + 1);
            }
        } else {
            int now = 1;
            for (int i = 0; i < n / 3 * 2 + 1; i++, now ^= 1) {
                printf("%d", now + 1);
            }
        }
        puts("");
    }
    return 0;
}