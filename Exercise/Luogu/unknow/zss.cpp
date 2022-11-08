#include <cstdio>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int a, x, y, z, s, h, b;
        scanf("%d%d%d%d%d%d%d", &a, &x, &y, &z, &s, &h, &b);
        if (a == 0) {
            puts("YES");
            continue;
        }
        int v0 = y - z;
        int v1 = v0 + b;
        int x0 = s / h;
        if (x0 >= x) {
            if (x * v0 >= a) {
                puts("YES");
            } else {
                puts("zss!");
            }
        } else {
            int x1 = x - x0;
            if (v0 * x0 + v1 * x1 >= a) {
                puts("YES");
            } else {
                puts("zss!");
            }
        }
    }
    return 0;
}