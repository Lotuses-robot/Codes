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
    double n, m, p, q;
    scanf("%lf%lf%lf%lf", &n, &m, &p, &q);
    if (n == 1) {
        printf("0");
        return 0;
    }
    double d = p / q / (0 + (1 - p / q) /  (n - 1));
    printf("%.8lf", d);
    return 0;
}