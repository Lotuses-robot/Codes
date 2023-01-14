// Copyright 2023 Lotuses
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>

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

#define eps 1e-6

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    int n, m;
    read(n, m);
    double left = -1e18, right = 1e18; bool fk = 0;
    for (int i = 1; i <= n; i++) {
        int a;
        read(a);
        left = std::max(left, (double) m / a / i);
        if (a != 1) fk = 1, right = std::min(right, (double) m / (a - 1) / i);
        // printf("%.2lf %.2lf\n", left, right);
    }
    if (!fk) {
        puts("xiaogougege");
    } else {
        int l = ceil(left - eps), r;
        if (fabs(right - floor(right)) < eps) r = floor(right) - 1;
        else r = floor(right);
        printf("%d\n", r - l + 1);
    }
    return 0;
}
