// Copyright 2022 Lotuses
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

typedef long long ll;

ll a, b;

ll dfs(ll x, ll y) {
    if (x > y)
        return 1e18;
    if (x << 1 > y)
        return y - x;
    return y & 1 ? dfs(x, y - 1) + 1 : dfs(x, y >> 1) + 1;
}

inline ll solve() {
    if (a == b)
        return 0;
    ll ans = 1e13, cnt = 0;
    do {
        ll res = dfs(a, b);
        ans = std::min(ans, res + cnt);
        if (a & 1) {
            a++;
        }
        else {
            a >>= 1;
        }
        cnt++;
    } while (a > 1);
    return ans;
}

int main() {
    int n;
    read(n);
    while (n--) {
        read(a, b);
        printf("%lld\n", solve());
    }
    return 0;
}
