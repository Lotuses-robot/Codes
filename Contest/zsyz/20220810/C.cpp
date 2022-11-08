#include <bits/stdc++.h>
using namespace std;

bool checker(int x, int y) { return 2 * x == 2 * y * (x / y) + y; }

int main() {
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        bool flag = 0;
        scanf("%d", &n);
        for (int i = 2; ; i++) {
            if (n / i - i / 2 < 0)
                break;

            if (n % i == 0 && i % 2) {
                printf("%d = ", n);
                for (int j = n / i - i / 2; j < n / i + i / 2; j++)
                    printf("%d + ", j);
                
                printf("%d\n", n / i + i / 2);
                flag = 1;
                break;
            } else if (checker(n, i)) {
                printf("%d = ", n);
                for (int j = n / i - i / 2 + 1; j < n / i + i / 2; j++)
                    printf("%d + ", j);
                printf("%d\n", n / i + i / 2);
                flag = 1;
                break;
            }
        }
        if (!flag)
            puts("IMPOSSIBLE");
    }
    return 0;
}
