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

int a[500005];

int main() {
    int n, x, k;
    read(n, x);

    for (int i = 0; i < n; i++) {
        read(k);
        a[k]++;
    }

    for (int i = 1; i < x; i++) {
        if (a[i] % (i + 1) != 0) {
            puts("No");
            return 0;
        } else {
            a[i + 1] += a[i] / (i + 1);
        }
    }

    puts("Yes");
    return 0;
}
