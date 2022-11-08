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

struct Int {
    int x;
    bool nan;

    bool operator < (Int b) const {
        if (nan || b.nan) return false;
        return x < b.x;
    }
};

Int a[500005];

void qsort(int l, int r) {
    if (l >= r) return;
    Int left = a[l];
    static Int b[114514];
    int Mid = l;
    int Bid = 0;
    for (int i = l + 1; i <= r; i++) {
        if (a[i] < left) {
            a[Mid] = a[i];
            Mid++;
        } else {
            b[Bid] = a[i];
            Bid++;
        }
    }
    for (int i = 0; i <= Bid - 1; i++) {
        a[Mid + i + 1] = b[i];
    }
    a[Mid] = left;
    qsort(l, Mid - 1);
    qsort(Mid + 1, r);
}

char ch[114514];

int main() {
    int T;
    read(T);
    while (T--) {
        int n;
        read(n);

        for (int i = 1; i <= n; i++) {
            scanf("%s", ch);
            if (ch[0] == 'n') {
                a[i].nan = true;
            } else {
                sscanf(ch, "%d", &a[i].x);
                a[i].nan = false;
            }
        }

        qsort(1, n);

        for (int i = 1; i <= n; i++) {
            if (a[i].nan) {
                printf("nan ");
            } else {
                printf("%d ", a[i].x);
            }
        }
        puts("");
    }
    return 0;
}
