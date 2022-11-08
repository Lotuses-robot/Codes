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

int a[20][20];
int f[1 << 20][20];

int main() {
    int n;
    read(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            read(a[i][j]);
        }
    }

    memset(f, 63, sizeof(f));

    // for (int i = 0; i < n; i++) {
    //     f[0][1 << i][i] = 0;
    //     v.push_back(1 << i);
    // }

    f[1][0] = 0;

    for (int i = 1; i < n; i++) {
        for (int st : clone) {
            for (int j = 0; j < n; j++) {
                if (((st >> j) & 1) == 0) {
                    int sto = st | (1 << j);
                    for (int k = 0; k < n; k++) {
                        if (((st >> k) & 1) == 0) continue;
                        f[sto][j] = std::min(f[sto][j],
                                                f[st][k] + a[k][j]);
                    }
                }
            }
        }
    }

    int ans = 1145141919;
    for (int k = 0; k < n; k++) {
        ans = std::min(ans, f[(1 << n) - 1][k] + a[k][0]);
    }

    printf("%d\n", ans);
    return 0;
}
