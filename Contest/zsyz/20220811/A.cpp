#include <cstdio>

#define min(a, b) ((a) < (b) ? (a) : (b))
#define ll long long

int doit(int n, int k) {
    int div = n % k;
    if (div == 0) return 0;
    else return k - div;
}

int main() {
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
    ll n, a, b, c;
    ll mn = 1e18 + 114514;
    int T;
    scanf("%d", &T);
    while (T--) {
        mn = 1e18 + 114514;
        scanf("%lld%lld%lld%lld", &n, &a, &b, &c);
        mn = min(mn, doit(n, a));
        mn = min(mn, doit(n, b));
        mn = min(mn, doit(n, c));

        printf("%lld\n", mn);
    }
    return 0;
}