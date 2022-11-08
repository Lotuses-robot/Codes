// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

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

int main() {
    int T;
    read(T);
    while (T--) {
        int n, x, gd;
        read(n, gd);
        for (int i = 1; i < n; i++) {
            read(x);
            gd = std::__gcd(gd, x);
        }

        if (gd == 1) {
            puts("0");
        } else if (std::__gcd(gd, n) == 1) {
            puts("1");
        } else if (std::__gcd(gd, n - 1) == 1) {
            puts("2");
        } else {
            puts("3");
        }
    }
}
