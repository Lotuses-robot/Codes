#include <cstdio>

#define int long long

int C(int n, int m) {
	if (m < n - m) m = n - m;
	int ans = 1;
	for (int i = m + 1; i <= n; i++) ans *= i;
	for (int i = 1; i <= n - m; i++) ans /= i;
	return ans;
}

int pow(int x, int y) {
    int base = x, ans = 1;
    do {
        if (y & 1) ans *= base;
        base *= base;
    } while (y >>= 1);
    return ans;
}

int calc(int m, int n, int w) {
    int ans = 0;
    for (int mx = 1; mx <= m; mx++) {
        ans += pow(mx - 1, n - w);
    }
    return ans;
}

signed main() {
    for (int n = 1; n <= 10; n++) {
        printf("%d ", n);
        for (int m = 1; m <= 10; m++) {
            // scanf("%lld%lld", &n, &m);

            int ans1 = 0;
            for (int i = 1; i <= n; i++) ans1 += i * C(n, i) * calc(m, n, i);

            printf("%lld ", ans1);
        }
        puts("");
    }
}