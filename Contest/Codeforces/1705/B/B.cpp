#include <cstdio>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, k;
        long long tot = 0;
        bool vis = 0;
        scanf("%d", &n);
        for (int i = 0; i < n - 1; i++) {
            scanf("%d", &k);
            if (k == 0) {
                if (vis) {
                    tot++;
                }
            } else {
                vis = true;
                tot += k;
            }
        }
        scanf("%d", &k);
        printf("%lld\n", tot);
    }
    return 0;
}