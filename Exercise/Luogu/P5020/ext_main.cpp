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

int a[114514];
bool f[25001];

int main() {
    int T;
    read(T);

    while (T--) {
        memset(f, 0, sizeof(f));
        int n, ans;
        read(n);
        ans = n;
        for (int i = 0; i < n; i++) read(a[i]);
        std::sort(a, a + n);
        f[0] = true;

        for (int i = 0; i < n; i++) {
            if (f[a[i]]) {
                ans--;
                continue;
            }
            for (int v = a[i]; v <= a[n - 1]; v++) {
                f[v] |= f[v - a[i]];
            }
        }

        printf("%d\n", ans);
    }
    return 0;
}
