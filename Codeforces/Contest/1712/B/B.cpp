#include <cstdio>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        int start;
        if (n % 2) {
            printf("%d ", 1);
            start = 2;
        } else {
            start = 1;
        }

        for (int i = start; i <= n; i += 2) {
            printf("%d %d ", i + 1, i);
        }
        puts("");
    }
    return 0;
}