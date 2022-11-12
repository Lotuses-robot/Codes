#include <cstdio>

const int mod = 998244353;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        long long n;
        scanf("%lld", &n);
        printf("%lld\n", n * (n - 1) / 2 % mod * (n - 2) % mod * (n - 2) % mod);
    }

    return 0;
}