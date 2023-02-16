// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

#define gc getchar()
template<typename T>
void read(T &r) {
    r = 0; static char ch, last;
    ch = gc, last = 'z';
    while (ch < '0' || ch > '9') last = ch, ch = gc;
    while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
    r = (last == '-') ? -r : r;
}

template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) {
    read(arg);
    read(arg_left...);
}

int a[114514];

int main() {
    #ifdef LOCAL
        freopen("ring3.in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    int n, m;
    read(n, m);
    for (int i = 0; i < n; i++) {
        read(a[i]);
    }
    std::sort(a, a + n);

    int l = 0, r = m - 1, ans = 1145141919;
    for (l = 0; r < n; l++, r++) {
        ans = std::min(ans, a[r] - a[l]);
    }
    printf("%d\n", ans);
    return 0;
}
