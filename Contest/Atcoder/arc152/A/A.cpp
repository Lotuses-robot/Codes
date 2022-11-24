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

int n, l;
int a, pt = 0;

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    read(n, l); bool flag = false;
    for (int i = 0; i < n; i++) {
        read(a);
        if (flag && a == 2) {
            puts("No");
            return 0;
        }
        if (flag) continue;
        pt++; pt += a;
        if (pt == l) flag = true;
        else if (pt == l + 1) {
            pt--; flag = true;
        } else if (pt == l + 2) {
            puts("No");
            return 0;
        }
    }
    puts("Yes");
    return 0;
}
