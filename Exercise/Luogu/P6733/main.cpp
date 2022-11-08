// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

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

#define maxn 114514
#define eps 1e-3

struct Node {
    int a, c;
} t[maxn];
double a[maxn];
int n, k;

bool check(double x) {
    // printf("debug ");
    for (int i = 0; i < n; i++) {
        a[i] = 1.0 * (t[i].c - x) * t[i].a;
        // printf("%.1lf ", a[i]);
    }
    // puts("");
    std::sort(a, a + n);

    int cnt = 0, j = n;
    for (int i = 0; i < n; i++) {
        while (a[i] + a[j - 1] >= eps && j >= i) j--;
        j = std::max(j, i + 1);
        cnt += n - j;
    }
    // printf("check %lf %d\n", x, cnt);
    return cnt >= k;
}

int main() {
    read(n, k);

    for (int i = 0; i < n; i++) {
        read(t[i].a, t[i].c);
    }

    double l = 1, r = 1.2e9;
    while (r - l > eps) {
        double mid = (l + r) / 2;
        if (check(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    printf("%.3lf\n", r);
    return 0;
}
