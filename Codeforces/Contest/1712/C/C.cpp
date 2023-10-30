#include <cstdio>
#include <cstring>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        static int a[100005];
        static bool tot[100005];
        memset(tot, 0, sizeof(tot));
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }

        int last;
        for (last = n - 2; last >= 0; last--) {
            if (a[last + 1] < a[last]) {
                break;
            }
        }
        last++;

        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (i < last) {
                if (!tot[a[i]]) {
                    ans++;
                }
                tot[a[i]] = true;
            } else {
                if (tot[a[i]]) {
                    for (int j = last; j < i + 1; j++) {
                        if (!tot[a[j]]) {
                            ans++;
                        }
                        tot[a[j]] = true;
                    }
                    last = i + 1;
                }
            }
        }

        printf("%d\n", ans);
    }
    return 0;
}