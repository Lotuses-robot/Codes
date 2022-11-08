#include <cstdio>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m;
        scanf("%d%d", &n, &m);
        if ((n + m - 1) % 2) {
            puts("Tonya");
        } else {
            puts("Burenka");
        }
    }
    return 0;
}