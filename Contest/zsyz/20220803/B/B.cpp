#include <cstring>
#include <cstdio>

#define ll long long

int main() {
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
    int T;
    scanf("%d", &T);

    while (T--) {
        ll n;
        scanf("%lld", &n);
        if (n == 0) {
            printf("%d\n", 0);
            continue;
        }

        ll l = 1, r = 1e9, mid, ans, sum;
        while (l <= r) {
            mid = (l + r) >> 1;
            sum = mid * (mid + 1) / 2;
            if (sum >= n) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        sum = ans * (ans + 1) / 2;
        if (sum - 1 == n) printf("%lld\n", ans + 1);
        else printf("%lld\n", ans);
    }
	return 0;
}