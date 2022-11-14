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

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    int n, ng = 0, po = 0, q;
    read(n);
    for (int i = 0; i < n; i++) {
        read(q);
        if (q == 1) po++;
        if (q == -1) ng++;
    }
    // ng++; int parts = po / ng, rem = po % ng;
    // for (int i = 0; i < ng; i++) {
    //     for (int j = 0; j < parts; j++) {
    //         printf("1 ");
    //     }
    //     if (i < rem) {
    //         printf("1 ");
    //     }
    //     if (i < ng - 1) printf("-1 ");
    // }
    for (int i = 0; i < n; i++) {
        if (ng != 0) {
            if (po != 0) {
                i++;
                printf("%d %d ", 1, -1);
                po--;
            } else {
                printf("%d ", -1);
            }
            ng--;
        } else {
            printf("%d ", 1);
            po--;
        }
    }
    return 0;
}
