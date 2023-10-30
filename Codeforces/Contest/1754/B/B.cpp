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
    int T;
    read(T);
    while (T--) {
        int n;
        read(n);
        int l = n / 2, r = n;
        if (n % 2)
            l++;
        for (int i = 0; i < n / 2; i++) {
            printf("%d %d ", l, r);
            l--, r--;
        }
        if (n % 2) {
            printf("%d\n", 1);
        }
    }
    return 0;
}
