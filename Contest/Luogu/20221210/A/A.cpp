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

int a[114514];

int main() {
    #ifdef LOCAL
        freopen("data/queries4.in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    int n, m;
    read(n, m);
    for (int i = 0; i < n; i++) {
        read(a[i]);
    }

    while (m--) {
        int x, y;
        read(x, y);
        a[x - 1] -= y;
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    return 0;
}
