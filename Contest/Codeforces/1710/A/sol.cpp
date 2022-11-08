// 1710A 
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

#define int long long

int a[114514], k;

bool cmp(int a, int b) {
    return a > b;
}

// n columns
bool check(int n, int m) {
    int los = 0;
    for (int i = 0; i < k; i++) {
        int mx = a[i] / m;
        if (mx < 2) continue;
        if (n < 2) {
            if (los == 0) {
                return false;
            } else {
                return true;
            }
        } else {
            mx = std::min(mx, n);
            n -= mx;
            los += (mx - 2);
        }
        if (n <= 0) return true;
    }
    return false;
}

signed main() {
    int T;
    scanf("%lld", &T);
    while (T--) {
        int n, m, taken = 0;
        scanf("%lld%lld%lld", &n, &m, &k);
        for (int i = 0; i < k; i++) {
            scanf("%lld", &a[i]);
        }
        std::sort(a, a + k, cmp);
        if (check(n, m) || check(m, n)) {
            puts("Yes");
        } else {
            puts("No");
        }
    }
    return 0;
}