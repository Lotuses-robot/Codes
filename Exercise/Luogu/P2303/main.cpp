#include <cmath>
#include <cstdio>

const int N = (1 << 16) + 5;
int n, tot, p[N];
bool flg[N];

void sieve(int n) {
    for (int i = 2; i <= n; ++i) {
        if (!flg[i])
            p[++tot] = i;
        for (int j = 1; j <= tot && i * p[j] <= n; ++j) {
            flg[i * p[j]] = 1;
            if (i % p[j] == 0)
                break;
        }
    }
}
long long phi(long long x) {
    long long ans = x;
    for (int i = 1; i <= tot && 1LL * p[i] * p[i] <= x; ++i) {
        if (x % p[i])
            continue;
        ans = ans / p[i] * (p[i] - 1);
        while (x % p[i] == 0)
            x /= p[i];
    }
    if (x > 1)
        ans = ans / x * (x - 1);
    return ans;
}
int main() {
    long long n, ans = 0;
    scanf("%lld", &n);
    sieve((int)sqrt(n));
    for (long long i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            ans += i * phi(n / i);
            if (i * i != n)
                ans += n / i * phi(i);
        }
    }
    printf("%lld\n", ans);
    return 0;
}
