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

int n;
int a[200005], amap[200005];
int b[200005], bmap[200005];

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n);
    for (int i = 0; i < n; i++) {
        read(a[i]); amap[a[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        read(b[i]); bmap[b[i]] = i;
    }

    int ans = 1; // [1, n]
    int l = 11451419, r = -11451419;

    // count MEX != 1
    for (int i = 1; i < n; i++) {
        int MEX = i + 1; // i hate MEX
        l = std::min(l, amap[i]);
        l = std::min(l, bmap[i]); 
        r = std::max(r, amap[i]);
        r = std::max(r, bmap[i]);
        // now we get [l, r] that valid for MEX -1.

        // printf("%d %d\n", l, r);

        int M1 = std::min(amap[MEX], bmap[MEX]), M2 = std::max(amap[MEX], bmap[MEX]);
        // then [0, M1 - 1], [M1 + 1, M2 - 1], [M2 + 1, n - 1];
        // for three square
        
        if (l >= 0 && r < M1) { // all in (1)
            ans += (l - 0 + 1) * (M1 - 1 - r + 1);
        } if (l > M1 && r < M2) { // all in (2)
            ans += (l - (M1 + 1) + 1) * (M2 - 1 - r + 1);
        } if (l > M2 && r < n) {
            ans += (l - (M2 + 1) + 1) * (n - 1 - r + 1);
        }
        // printf("%d\n", ans);
    }

    // count MEX = 1
    int M1 = std::min(amap[1], bmap[1]), M2 = std::max(amap[1], bmap[1]);

    // printf("%d %d\n", M2); 
    // printf("%d\n", ans);
    ans += M1 * (M1 - 1) / 2 + M1;
    // printf("%d\n", ans);
    ans += (M2 - M1 - 1) * (M2 - M1 - 2) / 2 + (M2 - M1 - 1);
    // printf("%d\n", ans);
    ans += (n - M2 - 1) * (n - M2 - 2) / 2 + (n - M2 - 1);

    printf("%lld\n", ans);
    return 0;
}
