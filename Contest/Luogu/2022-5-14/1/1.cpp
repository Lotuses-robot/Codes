#include <cstdio>

#define int long long
#define min(a, b) ((a) < (b) ? (a) : (b))

int main() {
    int T;
    scanf("%lld", &T);

    while (T--) {
        int x, y, z;
        scanf("%lld%lld%lld", &x, &y, &z);
        if (z - x < 1) {
            puts("Merry");
        } else {
            int maxn = (2*z - 1 - x) * x / 2;
            y -= maxn;
            if (y <= z - x) {
                puts("Renko");
            } else {
                puts("Merry");
            }
        }
    }
    return 0;
}