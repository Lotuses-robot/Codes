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

#define int long long
const int p = 998244353, maxn = 200005;

int inv[maxn], a[maxn], f[maxn], s[maxn];

void init() {
    inv[1] = 1;
    for (int i = 2; i <= maxn; i++) {
        inv[i] = (p - p / i) * inv[p % i] % p;
    }
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n;
    read(n);
    for (int i = 1; i < n; i++) {
        read(a[i]);
    }

    init();

    for (int i = n - 1; i >= 1; i--) {
        f[i] = ((a[i] + 1) + (s[i + 1] - s[i + a[i] + 1] + p) % p) % p * inv[a[i]] % p;
        s[i] = (s[i + 1] + f[i]) % p;
    }

    printf("%lld\n", f[1]);
    return 0;
}
