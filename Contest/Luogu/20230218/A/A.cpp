// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>

#define int long long

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

#define abs(x) ((x) >= 0 ? (x) : 0)

int mem[114514];

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        int n, k, a, b;
        read(n, k, a, b);
        if (n < k) {
            puts("0"); int now = 0;
            for (int i = 0; i < n; i++) putchar('a' + now), now ^= 1;
            puts("");
            continue;
        }
        bool is_fuck_last = false;
        // int ans = b * (n - k + 1), use = -1;
        int ans = 0x7fffffffffffffff, use = -1;
        for (int i = k - 1; i <= n; i++) {
            int nans = n / i * (abs(i - k + 1) * b + a);
            if (n % i != 0) {
                int len = n % i;
                int ans1 = abs(len - k + 1) * b;
                nans += ans1;
            } else {
                nans -= a;
            }
            if (nans < ans) {
                ans = nans;
                is_fuck_last = false;
                use = i;
            }

            int ans2 = (n / i - 1) * (abs(i - k + 1) * b + a);
            int len = n % i + i;
            ans2 += (len - k + 1) * b;

            if (ans2 < ans) {
                ans = ans2;
                is_fuck_last = true;
                use = i;
            }

            // printf("%d %d\n", i, nans);
            // mem[i] = nans;
        }

        printf("%lld\n", ans);
        if (use == -1) {
            int now = 0;
            for (int i = 0; i < n; i++) {
                putchar('a' + now);
                now ^= 1;
            }
            while (true); 
        } else {
            int now = 0;
            for (int i = 1; i <= n; i++) {
                putchar('a' + now);
                if (i % use || (i % use == 0 && n / use == i / use && is_fuck_last)) now ^= 1;
            }
        }
        puts("");
    }
    return 0;
}
