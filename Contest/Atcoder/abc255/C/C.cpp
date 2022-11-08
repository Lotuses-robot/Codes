#include <cstdio>

#define min(x, y) (((x) < (y)) ? (x) : (y))
#define abs(x) ((x) > 0 ? (x) : -(x))

void swap(long long &a, long long &b) {
    long long k = a;
    a = b;
    b = k;
}

int main() {
    long long x, a, d, n;
    scanf("%lld%lld%lld%lld", &x, &a, &d, &n);
    if (d == 0) {
        printf("%lld\n", abs(x - a));
        return 0;
    }
    long long s = a, t = a + (n - 1) * d;
    if (s > t) swap(s, t);
    if (x <= s) {
        printf("%lld\n", s - x);
    } else if (x >= t) {
        printf("%lld\n", x - t);
    } else {
        printf("%lld\n", min((x - s) % d, d - (x - s) % d));
    }
    return 0;
}
/*
1000000000000050000
1000000000000000000
1000000
1000000000000
*/