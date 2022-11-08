// Copyright 2022 Lotuses
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>

#define gc getchar()
template<typename T>
void read(T &r) { // NOLINT
    r = 0; static char ch, last; // NOLINT
    ch = gc, last = 'z';
    while (ch < '0' || ch > '9') last = ch, ch = gc;
    while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
    r = (last == '-') ? -r : r;
}

template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) { // NOLINT
    read(arg);
    read(arg_left...);
}

#define ll long long

ll check(ll mx) {
    ll k = 2, ans = 0;
    while (k * k * k <= mx) {
        ans += mx / (k * k * k);
        k++;
    }
    return ans;
}

int main() {
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
    ll n;
    read(n);
    ll l = 7, r = 1e18 + 1000, mid, ans;
    while (l < r) {
        mid = l + (r - l >> 1);
        ans = check(mid);
        if (ans < n) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    // printf("%d\n", check(r));
    if (check(r) != n) {
        puts("-1");
        return 0;
    }
    printf("%lld\n", r);
    return 0;
}
