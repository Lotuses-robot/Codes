#include <cstdio>

#define int long long

signed main() {
    static int a[1000006], 
               qr[1000006];
    int n, c, q;
    scanf("%lld%lld%lld", &n, &c, &q);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    while(q--) {
        int len;
        scanf("%lld", &len);
        int mx = -998244353, mxi, mn = 998244353, mni, sum = 0;
        for (int i = 0; i < len; i++) {
            scanf("%lld", &qr[i]); qr[i]--;
            sum += a[qr[i]];
            if (a[qr[i]] > mx) {
                mx = a[qr[i]];
                mxi = i;
            }
            if (a[qr[i]] < mn) {
                mn = a[qr[i]];
                mni = i;
            }
        }
        // printf("%d %d %d\n", mx, mn, sum);
        int ans = mn - (sum - mx - mn) - 2 * mx + c * (len - 1);
        printf("%lld\n", ans);
    }
    return 0;
}