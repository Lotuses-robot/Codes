// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>

#define int long long

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

signed main() {
    #ifdef LOCAL
        freopen("data/19.in", "r", stdin);
        freopen("data/19.out", "w", stdout);
    #endif
    
    int n;
    read(n);
    if (n == 1) {
        printf("%d\n", 1);
        return 0;
    }
    int ans = 28 + (n * n - 4) * 3 + (n - 2) * 3 * 2;
    printf("%lld\n", ans);
    return 0;
}
