// Copyright 2023 Lotuses
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>

#define int long long

#define gc getchar()
template<typename T>
void read(T &r) {
    r = 0; static char ch, last;
    ch = gc, last = 'z';
    while (ch < '0' || ch > '9') last = ch, ch = gc;
    while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
    r = (last == '-') ? -r : r;
}

template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) {
    read(arg);
    read(arg_left...);
}

#define eps 1e-12
#define flr(x) (int)(floor(x + eps))

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    int T;
    read(T);
    while (T--) {
        int a, b, n, m;
        read(a, b, n, m);
        int c1 = (n - flr(1.0 * n / (m + 1))) * a;
        int c2 = n / (m + 1) * m * a + (n - flr(1.0 * n / (m + 1)) * (m + 1)) * b;
        int c3 = b * n;
        int ans = std::min(c1, std::min(c2, c3));
        printf("%lld\n", ans, c1, c2, c3);
    }
    return 0;
}

/*
1: all choose a
c = (n - floor(n / (m + 1))) * a

2: choose a for free & some b
c = a * n * m / (m + 1)      +       (n - floor(n / (m + 1)) * (m + 1)) * b

3: all choose b
c = b * n
*/