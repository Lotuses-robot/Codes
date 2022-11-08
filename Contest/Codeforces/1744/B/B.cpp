// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>

#define int long long

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

signed main() {
    int T;
    read(T);
    while (T--) {
        int n, q, s = 0;
        read(n, q);
        for (int i = 0; i < n; i++) {
            read(a[i]);
            s += a[i];
        }
            // puts("fk");

        int esum = 0, osum = 0;
        while (q--) {
            int t, x;
            read(t, x);


            switch (t) {
                case 0:
                    osum += x;
                    break;
                case 1:
                    esum += x;
                    break;
            }

            int ans = s + esum * (n / 2) + osum * (n / 2);
            if (n & 1) {
                ans += osum;
            }
            printf("%lld\n", ans);
        }
    }
    return 0;
}
