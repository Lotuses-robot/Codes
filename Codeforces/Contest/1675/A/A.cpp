#include <cstdio>

#define max(x, y) ((x) > (y) ? (x) : (y))

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        int a, b, c, x, y;
        scanf("%d%d%d%d%d", &a, &b, &c, &x, &y);
        x -= a;
        y -= b;
        x = max(0, x);
        y = max(0, y);
        if (x + y <= c) {
            puts("YES");
        } else {
            puts("NO");
        }
    }
    return 0;
}