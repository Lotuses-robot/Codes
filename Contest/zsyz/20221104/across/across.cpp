// Copyright 2022 Lotuses
#include <cmath>
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

int n, w, u, v, t1, t2;
double T;

#define eps 1e-4

struct UnSafe {
    double l, r;
    bool operator < (UnSafe b) const {
        if (fabs(l - b.l) > eps) return l < b.l;
        return r < b.r;
    }
};
std::vector<UnSafe> list;

int main() {
    #ifdef LOCAL
        freopen("across.in", "r", stdin);
        freopen("across.out", "w", stdout);
    #endif
    read(n, w, u, v, t1, t2);
    T = (double) w / v;
    for (int i = 0; i < n; i++) {
        static char pos[10];
        static int m, l, p, fac;

        scanf("%s", pos);
        fac = (pos[0] == 'W') ? 1 : -1;

        read(m);
        for (int j = 0; j < m; j++) {
            read(l, p);
            double s = (double) fac * p / u - i * T;
            double t = s + (double) l / u;
            // printf("%lf %lf\n", s, t);
            list.push_back({s, t});
        }
    }
    // puts("input done");

    std::sort(list.begin(), list.end());

    double ans = 0;
    double l = -1;
    for (UnSafe u : list) {
        if (l == -1) {
            l = u.r;
            if (u.l >= t1) ans = std::max(ans, u.l - t1 - T);
        } else if (u.l >= l && u.l >= t1) {
            // printf("%lf %lf\n", l, u.l);
            ans = std::max(ans, std::min(u.l, (double) t2) - std::max(l, (double) t1) - T);
        }
        l = std::max(l, u.r);
        if (l - t2 > eps) {
            break;
        }
    }

    if (l <= t2) {
        ans = std::max(ans, t2 - l);
    }

    printf("%.4lf\n", ans);
    return 0;
}
