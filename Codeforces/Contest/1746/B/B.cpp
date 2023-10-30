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

int a[114514];

int main() {
    // #ifdef LOCAL
        // freopen(".in", "r", stdin);
        // freopen(".out", "w", stdout);
    // #endif
    
    while (true);

    int T;
    read(T);
    while (T--) {
        int n; bool flag = true;
        read(n);
        for (int i = 0; i < n; i++) {
            read(a[i]);
            if (i > 0 && a[i - 1] > a[i]) flag = false;
        }
        // if (flag) {
        //     puts("0");
        //     continue;
        // }

        int ans = 0;
        int r = n - 1, l = 0;
        while (l < r) {
            while (l < r && a[r] == 1) r--;
            if (l >= r) {
                break;
            }
            while (l < r && a[l] == 0) l++;
            if (l >= r) {
                break;
            }
            l++; r--;
            ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}
