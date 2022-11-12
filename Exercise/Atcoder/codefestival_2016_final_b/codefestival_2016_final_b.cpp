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

int n;
int check(int q) {
    int s = (1 + q) * q / 2;
    if (s < n) {
        return true;
    } else {
        return false;
    }
}

int main() {
    read(n);
    
    int l = 1, r = 1e4;
    while (r - l > 5) {
        int mid = (l + r) >> 1;
        if (check(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    int i;
    for (i = l; i <= r; i++) {
        if (!check(i)) {
            break;
        }
    }
    int q = (i + 1) * i / 2 - n;
    for (int j = 1; j <= i; j++) {
        if (j != q) {
            printf("%d\n", j);
        }
    }
    return 0;
}
