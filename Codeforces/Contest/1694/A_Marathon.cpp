#include <cstdio>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        int tot = 0;
        if (a < b) {
            tot++;
        }
        if (a < c) {
            tot++;
        }
        if (a < d) {
            tot++;
        }
        printf("%d\n", tot);
    }
    return 0;
}