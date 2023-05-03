// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <ctime>
#include <random>

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
    #ifdef LOCAL
        freopen("data/17.in", "w", stdout);
    #endif
    std::mt19937 rd(time(NULL));
    printf("%d\n", rd() % (int)(1e9 - 1) + 2);
}
