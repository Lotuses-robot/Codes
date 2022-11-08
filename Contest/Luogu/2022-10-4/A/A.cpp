#include <cstdio>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        long long l, r;
        scanf("%lld%lld", &l, &r);
        
        if (l % 2 && r % 2) {
            printf("%lld\n", (r - l + 1) / 2 + 1);
        } else {
            printf("%lld\n", (r - l + 1) / 2);
        }
    }
    return 0;
}