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

int a[1145141];
int sf[1145141];
int nx[1145141];

int main() {
    int n;
    read(n);
    for (int i = 0; i < n; i++) {
        read(a[i]);
    }

    if (a[0] == 1) {
        int ans = 0;
        for (int i = 1; i < n; i++) {
            ans += 1 - a[i];
        }
        printf("%d\n", ans);
    } else if (a[0] == 0) {
        int ans = 0, pt;
        for (int i = 1; i < n; i++) {
            if (a[i] == -1) {
                ans = -1;
                break;
            }
            if (a[i] == 1) {
                pt = i;
            }
        }
        if (ans == -1) {
            puts("BRAK");
            return 0;
        }
        for (int i = pt + 1; i < n; i++) {
            ans += 1 - a[i];
        }
    } else {
        int las = n;
        for (int i = n - 1; i >= 0; i--) {
            sf[i] = sf[i + 1] + (1 - a[i]);
            nx[i] = las;
            if (a[i]) {
                las = i;
            }
        }

        int ans = 1145141919, cnt = 0;
        for (int i = 0; i < n; i++) {
            cnt += a[i] + 1;
            if (a[nx[i]] != -1) ans = std::min(ans, cnt + sf[nx[i]]);
            if (i < n - 1 && a[i + 1] == 1) ans = std::min(ans, cnt + 1 + sf[nx[i + 1]]);
        }
        if (ans == 1145141919) {
            puts("BRAK");
        } else {
            printf("%d\n", ans);
        }
    }
    return 0;
}
