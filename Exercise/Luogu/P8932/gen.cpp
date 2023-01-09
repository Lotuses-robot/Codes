// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

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
        // freopen("", "r", stdin);
        freopen(".in", "w", stdout);
    #endif
    srand(time(NULL));

    int q = 10000, n = 100;
    printf("%d\n", q);
    for (int i = 0; i < n; i++) {
        putchar(rand() % 26 + 'a');
    }
    puts("");
    while (q--) {
        int p = rand() % 100 + 1;
        char c = rand() % 26 + 'a';
        printf("%d %c\n", p, c);
    }
    return 0;
}
