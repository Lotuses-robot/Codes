// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <bits/extc++.h>
#include <windows.h>

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


int a[500005], s[500005];

#define int long long 

__gnu_pbds::tree<std::pair<int, int>, __gnu_pbds::null_type, std::less<std::pair<int, int> >,
                __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> bst;

signed main() {
    // Sleep(10000);
    freopen("466C.in", "r", stdin);
    freopen("466C.out", "w", stdout);
    int n, sum = 0;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
        sum += a[i];
        if (i > 1) {
            s[i] = s[i - 1] + a[i];
        }
    }
    
    if (sum % 3) {
        puts("0");
        return 0;
    }

    for (int i = 3; i <= n; i++) {
        // printf("inserted %d\n", s[n] - s[i - 1]);
        bst.insert(std::make_pair(s[n] - s[i - 1], i));
    }

    int nsum = a[1], dec = a[1], ans = 0;
    for (int i = 2; i <= n; i++) {
        // printf("debug %d\n", nsum);
        std::pair<int, int> x = std::make_pair(nsum /*+ dec*/, 0ll),
             y = std::make_pair(nsum /*+ dec */+ 1, 0ll),
             z = std::make_pair(s[n] - s[i], i + 1);

        int rec1 = bst.order_of_key(y), rec2 = bst.order_of_key(x);
        if (nsum == sum / 3) ans += rec1 - rec2;
        // printf("%d %d %d %d\n", x.first, y.first, rec1, rec2);
        if (z.second <= n && !bst.erase(z)) exit(-1);
        dec += a[i]; nsum += a[i];
    }

    printf("%lld\n", ans);
    return 0;
}
