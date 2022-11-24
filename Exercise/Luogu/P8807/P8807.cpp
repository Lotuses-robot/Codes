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

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        int n, m;
        read(n, m);
        if (m >= 20) {
            puts("Yes");
            goto small_tang_ak_ioi;
        }
        for (int i = 1; i <= m; i++){
            if (n % i != i - 1) {
                puts("Yes");
                goto small_tang_ak_ioi;
            }
        }

        puts("No");
        small_tang_ak_ioi:if (0) puts("Small_Tang AK IOI!");
    }
    return 0;
}
