#include <cstdio>
#include <algorithm>

int a[314514];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int cnt = 0, last = 0;
    std::sort(a, a + n);
    for (int i = 0; i < n; i++) {
        if (a[i] > last + 1) {
            if (cnt >= 2) {
                cnt -= 2;
            } else if (cnt == 1) {
                n--;
                cnt--;
                if (i > n) {
                    break;
                }
                i--;
            } else {
                n -= 2;
                // printf("%d %d\n", n, i);
                if (i > n) {
                    break;
                }
                i--;
            }
            last++;
        } else if (a[i] == last + 1) {
            last++;
        } else if (a[i] == last) {
            cnt++;
        }
    }
    printf("%d\n", last + cnt / 2);
    return 0;
}