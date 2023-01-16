快速幂模板。

```cpp
// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>

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

#define int long long

int qpow(int a, int b, int p) {
    int base = a, ans = 1;
    do  {
        if (b & 1) ans *= base, ans %= p;
        base *= base; base %= p;
    } while (b >>= 1);
    return ans;
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    int p, a, b;
    read(p, a, b);
    printf("%lld\n", qpow(a, b, p));
    return 0;
}

```