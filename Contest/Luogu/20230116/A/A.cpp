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

const int A = 400, B = 600;
#define flt(x) (floor((x) + 0.500001))

bool check(int a, int b, int cc) {
    double c = 1000.0 * a / A + 1000.0 * b / B;
    if (int(flt(c)) == cc) return true;
    return false;
}

void find(int c, int &a, int &b) {
    for (b = 0; b <= 600; b++) {
        int a1 = 1.0 * A * c / 1000 - 1.0 * A * b / B;
        int a2 = ceil(1.0 * A * c / 1000 - 1.0 * A * b / B);
        if (a1 <= 400 && check(a1, b, c)) {a = a1; return;}
        if (a2 <= 400 && check(a2, b, c)) {a = a2; return;}
    }
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    int n;
    read(n);
    for (int i = 0; i < n; i++) {
        int c, a, b;
        read(c);
        find(c, a, b);
        printf("%d %d\n", a, b);
    }
    return 0;
}
