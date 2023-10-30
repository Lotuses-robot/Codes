#include <cstdio>
#include <algorithm>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, x;
        static int num[1000];
        scanf("%d%d", &n, &x);
        for (int i = 0; i < 2 * n; i++) {
            scanf("%d", &num[i]);
        }
        std::sort(num, num + 2 * n);
        int l = 0, r = n;
        bool flag = true;
        while (l < n) {
            if (num[r] - num[l] < x) {
                flag = false;
                break;
            }
            l++; r++;
        }
        if (flag) {
            puts("YES");
        } else {
            puts("NO");
        }
    }
    return 0;
}