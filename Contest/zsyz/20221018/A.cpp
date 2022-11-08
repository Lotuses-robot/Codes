// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>

#define gc getchar()
template <typename T> void read(T &r) { // NOLINT
    r = 0;
    static char ch, last; // NOLINT
    ch = gc, last = 'z';
    while (ch < '0' || ch > '9')
        last = ch, ch = gc;
    while (ch >= '0' && ch <= '9')
        r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
    r = (last == '-') ? -r : r;
}

template <typename T, typename... Ts>
void read(T &arg, Ts &...arg_left) { // NOLINT
    read(arg);
    read(arg_left...);
}

const int maxn = 1000006;

int color[maxn],
    dfn[maxn],
    nxt[maxn],
    minn[maxn],
    cd[maxn];

int n;

int main() {
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
    read(n);
    for (int i = 1; i <= n; i++) {
        read(nxt[i]);
    }

    for (int cow = 1; cow <= n; cow++) {
        for (int i = cow, cnt = 0;; i = nxt[i], cnt++) {
            if (!color[i]) {
                color[i] = cow;
                dfn[i] = cnt;
            } else if (color[i] == cow) {
                minn[cow] = cnt - dfn[i];
                cd[cow] = dfn[i];
                printf("%d\n", cnt);
                break;
            } else {
                minn[cow] = minn[color[i]];
                cd[cow] = cnt + std::max(cd[color[i]] - dfn[i], 0);
                printf("%d\n", cd[cow] + minn[cow]);
                break;
            }
        }
    }
    return 0;
}
