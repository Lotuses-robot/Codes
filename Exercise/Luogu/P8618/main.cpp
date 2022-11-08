// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <set>
#include <vector>

#define ll long long

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

int a[114514];
std::set<int> s;

int main() {
    int n, m;
    ll sum = 0;

    read(n, m);
    for (int i = 0; i < n; i++) {
        read(a[i]);
        s.insert(i);
        sum += a[i];
    }

    while (m--) {
        int l, r;
        read(l, r);
        l--, r--;
        std::set<int>::iterator p = s.lower_bound(l);
        while (p != s.end() && *p <= r) {
            // printf("%d %d %d\n", *p, a[*p], std::__lg(a[*p]));
            sum -= a[*p] - std::__lg(a[*p]) - 1;
            a[*p] = std::__lg(a[*p]) + 1;
            if (a[*p] <= 2) {
                p = s.erase(p);
            } else {
                p++;
            }
        }
        printf("%lld\n", sum);
    }
    return 0;
}
