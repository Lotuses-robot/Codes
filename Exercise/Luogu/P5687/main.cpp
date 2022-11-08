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

int a[314514],
    b[314514];
int main() {
    int n, m;
    read(n, m);
    int min1 = 1145141919, min2 = 1145141919, s1 = 0, s2 = 0;

    for (int i = 0; i < n; i++) {
        read(a[i]);
        min1 = std::min(a[i] * (m - 1), min1);
        s1 += a[i] * (m - 1);
    } for (int i = 0; i < m; i++) {
        read(b[i]);
        min2 = std::min(b[i] * (n - 1), min2);
        s2 += b[i] * (n - 1);
    }

    // printf("%d %d %d %d\n", min1, min2, s1, s2);

    int ans1 = min2 + s1, ans2 = min1 + s2;
    int ans = std::min(ans1, ans2);
    printf("%d\n", ans - 3);
    return 0;
}
