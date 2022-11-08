#include <cstdio>
#include <map>

#define ll long long

std::map<int, ll> mp;

int main() {
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
    int n;
    ll ans = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int p;
        scanf("%d", &p);
        ans += mp[p] * (n - i + 1);
        mp[p] += i;
    }
    printf("%lld\n", ans);
    return 0;
}