// Copyright 2023 Lotuses
#include <ctime>
#include <cstdio>
#include <cstring>
#include <vector>
#include <random>

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

std::mt19937 rng(time(0));


int main() {
    #ifdef LOCAL
        freopen(".in", "w", stdout);
    #endif
    
    int T = 1000;
    printf("%d\n", T);
    for (int i = 0; i < T; i++) {
        int n = rng() % 10000 + 2;
        printf("%d %d %d %d\n", n, n, rng() % 50000 + 2, rng() % 50000 + 2);
    }
    return 0;
}
