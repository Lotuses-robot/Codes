// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>

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
    long long x, k;
    read(x, k);
    
    for (int i = 0; i < k; i++) {
        double xx = x / 10.0;
        x = (long long)(xx + 0.5);
    }

    x = x * pow(10, k);
    
    printf("%lld\n", x);
}
